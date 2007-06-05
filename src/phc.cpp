/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Main application module 
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ltdl.h>
#include "cmdline.h"
#include "process_ast/process_ast.h"
#include "codegen/Lift_functions_and_classes.h"
#include "codegen/Generate_C.h"
#include "codegen/Lower_control_flow.h"
#include "codegen/Lower_expr_flow.h"
#include "codegen/Note_top_level_declarations.h"
#include "codegen/Shredder.h"
#include "codegen/Goto_uppering.h"
#include "codegen/Check_lowering.h"
#include "codegen/Check_uppering.h"
#include "process_ast/Strip_comments.h"
#include "process_ast/Invalid_check.h"
#include "process_ast/PHP_unparser.h"
#include "process_ast/XML_unparser.h"
#include "process_ast/DOT_unparser.h"
#include "AST.h"
#include "parsing/parse.h"
#include "embed/embed.h"

using namespace std;

struct gengetopt_args_info args_info;

void generate_c(AST_php_script* php_script, ostream& os = cout);
void run_plugins(AST_php_script* php_script);

void sighandler(int signum)
{
	switch(signum)
	{
		case SIGABRT:
			printf("SIGABRT received!\n");
			break;
		case SIGSEGV:
			printf("SIGSEGV received!\n");
			break;
		default:
			printf("Unknown signal received!\n");
			break;
	}

	printf("This could be a bug in phc. If you suspect it is, please email\n");
	printf("a bug report to phc-general@phpcompiler.org.\n");
	exit(-1);
}




int main(int argc, char** argv)
{
	AST_php_script* php_script = NULL;

	// Start the embedded interpreter
	PHP::startup_php ();

	// Synchronise C and C++ I/O
	ios_base::sync_with_stdio();

	// catch a seg fault - note this doesnt harm gdb, which will override this.
	// We do this so that tests will still continue if theres a seg fault
	signal(SIGSEGV, sighandler);
	signal(SIGABRT, sighandler);

	// Parse command line parameters 
	if(cmdline_parser(argc, argv, &args_info) != 0)
		exit(-1);

	if(args_info.inputs_num == 0)
	{
		php_script = parse(new String("-"), NULL, args_info.read_ast_xml_flag);
	}
	else
	{
		php_script = parse(new String(args_info.inputs[0]), NULL, args_info.read_ast_xml_flag);
		if (php_script == NULL)
		{
			phc_error("File not found", new String(args_info.inputs[0]), 0);
		}
	}

	// Check for invalid but parsable code
	Invalid_check ic;
	php_script->visit (&ic);
	ic.use_ice = true; // from now on, use an internal error

	if(php_script == NULL) return -1;

	// Make sure the inputs cannot be accessed globally
	args_info.inputs = NULL;


	process_ast(php_script);


	// check for errors
	php_script->visit (&ic); 
	assert (php_script->is_valid ());

	// do this early
	Note_top_level_declarations ntld;
	php_script->visit (&ntld);

	// lift
	if(args_info.run_lifting_flag
		|| args_info.generate_c_flag
		|| args_info.compile_flag)
	{
		Lift_functions_and_classes lift;
		php_script->transform_children(&lift);

		// check for errors
		php_script->visit (&ic);
	}

	// lower
	if (args_info.run_lowering_flag 
			|| args_info.run_shredder_flag
			|| args_info.obfuscate_flag
			|| args_info.generate_c_flag
			|| args_info.compile_flag)
	{
		Lower_control_flow lcf;
		php_script->transform_children (&lcf);
		php_script->visit (&ic); // check for errors
		assert (php_script->is_valid ());

		Lower_expr_flow lef;
		php_script->transform_children (&lef);
		php_script->visit (&ic); // check for errors
		assert (php_script->is_valid ());

		Check_lowering cl;
		php_script->visit (&cl);
		php_script->visit (&ic); // check for errors
		assert (php_script->is_valid ());
	}

	// shred
	if(args_info.run_shredder_flag
			|| args_info.obfuscate_flag
			|| args_info.generate_c_flag
			|| args_info.compile_flag)
	{
		Shredder s;
		php_script->transform_children(&s);
		php_script->visit (&ic); // check for errors
		assert (php_script->is_valid ());
	}

	// upper (implied by obfuscation)
	if(args_info.run_goto_uppering_flag || args_info.obfuscate_flag)
	{
		Goto_uppering gu;
		php_script->visit (&gu);
		php_script->visit (&ic); // check for errors
		assert (php_script->is_valid ());

		Check_uppering cl;
		php_script->visit (&cl);
		php_script->visit (&ic); // check for errors
		assert (php_script->is_valid ());
	}

	// Strip comments
	if (args_info.obfuscate_flag)
	{
		Strip_comments sc;
		php_script->visit (&sc);
		php_script->visit (&ic);
		assert (php_script->is_valid ());
	}

	run_plugins(php_script);

	if(args_info.pretty_print_flag
		|| args_info.obfuscate_flag) // obfuscate implies printing now
	{
		PHP_unparser php_unparser;
		php_script->visit(&php_unparser);
	}

	if(args_info.dump_ast_xml_flag)
	{
		XML_unparser xml_unparser;
		php_script->visit(&xml_unparser);
	}

	if(args_info.dump_ast_dot_flag)
	{
		DOT_unparser dot_unparser;
		php_script->visit(&dot_unparser);
	}
	
	if(args_info.generate_c_flag)
	{
		generate_c(php_script);
	}

	if(args_info.compile_flag)
	{
		// Find PHP installation path
		char* php_path;
		if(args_info.with_php_given)
			php_path = args_info.with_php_arg;
		else
			php_path = PHP_INSTALL_PATH;

		// Generate C
		stringstream ss;
		generate_c(php_script, ss);
		
		// Argument array for gcc
		#define GCC_ARGS 10
		stringstream args[GCC_ARGS];
		args[0] << "gcc";
		args[1] << "-I" << php_path << "/include/php";
		args[2] << "-I" << php_path << "/include/php/main";
		args[3] << "-I" << php_path << "/include/php/TSRM";
		args[4] << "-I" << php_path << "/include/php/Zend";
		args[5] << "-L" << php_path << "/lib";
		args[6] << "-Wl,-R" << php_path << "/lib";
		args[7] << "-lphp5";
		args[8] << "-xc";
		args[9] << "-";

		char** argv;
		argv = (char**) calloc(GCC_ARGS + args_info.c_option_given + 1, sizeof(char*));
		for(unsigned i = 0; i < GCC_ARGS; i++) 
			argv[i] = strdup(args[i].str().c_str());
		for(unsigned i = 0; i < args_info.c_option_given; i++)
			argv[GCC_ARGS + i] = args_info.c_option_arg[i]; 
		argv[GCC_ARGS + args_info.c_option_given] = NULL;

		if(args_info.verbose_flag)
		{
			for(unsigned i = 0; i < GCC_ARGS + args_info.c_option_given; i++)
				cout << argv[i] << " ";
			cout << endl;
		}

		// Pipe output of Generate_C into gcc
		int pfd[2];
		#define READ_END 0
		#define WRITE_END 1
		if(pipe(pfd) == -1) 
		{
			cerr << "Could not create pipe" << endl;
			exit(-1);
		}

		int cpid = fork();
		if(cpid == -1)
		{
			cerr << "Could not fork" << endl;
			exit(-1);
		}

		if(cpid == 0)
		{
			// Child (gcc)
			close(pfd[WRITE_END]);
			dup2(pfd[READ_END], STDIN_FILENO);
			execvp("gcc", argv);
		}
		else
		{
			// Parent (phc)
			// Backup old stdout
			int old_stdout = dup(STDOUT_FILENO);

			// Redirect stdout to the pipe
			close(pfd[READ_END]);
			dup2(pfd[WRITE_END], STDOUT_FILENO);

			// Output previously generated C
			cout << ss.str ();
			cout.flush();

			// Close the pipe into indicate EOF to gcc
			close(STDOUT_FILENO);
			close(pfd[WRITE_END]);

			// Wait for gcc to finish
			waitpid(cpid, NULL, 0);

			// Restore stdout
			dup(old_stdout);
			close(old_stdout);
		}
	}

	PHP::shutdown_php ();

	return 0;
}
		
void generate_c(AST_php_script* php_script, ostream& os)
{
	Generate_C* generate_c;

	if(!args_info.extension_given)
		generate_c = new Generate_C(NULL);
	else
		generate_c = new Generate_C(new String(args_info.extension_arg));

	// adding an ostream is so invasive, thats its simpler to simply hack in this osteam as a global.
	streambuf* backup = cout.rdbuf ();
	cout.rdbuf (os.rdbuf ());
	php_script->visit(generate_c);
	cout.rdbuf (backup);
}


#define ERR_PLUGIN_UNKNOWN  "Unknown error (%s) with plugin %s"
void 
run_plugins(AST_php_script* php_script)
{
	typedef void (*process_ast_function)(AST_php_script*);
	int ret = lt_dlinit();
	if (ret != 0) phc_error (ERR_PLUGIN_UNKNOWN, lt_dlerror ());

	for(unsigned i = 0; i < args_info.run_given; i++)
	{
		// Try opening the specified plugin from its default location, 
		// from the current working directory, and from PKGLIBDIR (in that order)
		lt_dlhandle handle = lt_dlopenext (args_info.run_arg[i]);

		const char* default_err;
		const char* cwd_err;
		char in_cwd[256];
		if(handle == NULL)
		{
			// we record multiple errors, so need strdup, or they'll oerv-write each other
			default_err = strdup (lt_dlerror ()); 

			// Try current directory
			getcwd(in_cwd, 256);

			// TODO insecure
			strcat(in_cwd, "/");
			strcat(in_cwd, args_info.run_arg[i]);
			handle = lt_dlopenext (in_cwd);
		}

		const char* datadir_err;
		char in_datadir[256];
		if(handle == NULL)
		{
			cwd_err = strdup (lt_dlerror ());

			// Try installed dir
			// TODO insecure 
			strcpy(in_datadir, PKGLIBDIR);
			strcat(in_datadir, "/");
			strcat(in_datadir, args_info.run_arg[i]);
			handle = lt_dlopenext (in_datadir);	
		}

		if(handle == NULL)
		{
			datadir_err = strdup (lt_dlerror ());
			phc_error (
				"Could not find %s plugin with errors \"%s\", \"%s\" and \"%s\"",
				NULL, 0, args_info.run_arg[i], default_err, cwd_err, datadir_err);
		}

		process_ast_function past = (process_ast_function) lt_dlsym(handle, "process_ast");
		const char* load_symbol_err = lt_dlerror();
		if(past == NULL)
		{
			phc_error ("Unknown error (%s) with plugin %s", NULL, 0, args_info.run_arg[i], load_symbol_err);
		}

		(*past)(php_script);
		
		int ret = lt_dlclose (handle);
		if (ret != 0) phc_error (ERR_PLUGIN_UNKNOWN, NULL, 0, lt_dlerror ());
	}

	ret = lt_dlexit();
	if (ret != 0) phc_error (ERR_PLUGIN_UNKNOWN, NULL, 0, lt_dlerror ());

#undef ERR_PLUGIN_UNKNOWN
}
