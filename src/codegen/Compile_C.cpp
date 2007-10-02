/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compile generated C code
 */

#include "codegen/Compile_C.h"
#include <vector>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

Compile_C::Compile_C (stringstream& os)
: os(os)
{
	this->name = new String ("compile_c");
}

stringstream& new_arg (vector<stringstream*> &args)
{
	stringstream* stream = new stringstream;
	args.push_back (stream);
	return *stream;
}

void Compile_C::run (AST_php_script* in, Pass_manager* pm)
{
	if (not pm->args_info->compile_flag)
		return;

	// Find PHP installation path
	const char* php_path;
	if(pm->args_info->with_php_given)
		php_path = pm->args_info->with_php_arg;
	else
		php_path = PHP_INSTALL_PATH;


	// Argument array for gcc
	vector<stringstream*> args;
	new_arg (args) << "gcc";
	new_arg (args) << "-I" << php_path << "/include/php";
	new_arg (args) << "-I" << php_path << "/include/php/main";
	new_arg (args) << "-I" << php_path << "/include/php/TSRM";
	new_arg (args) << "-I" << php_path << "/include/php/Zend";
	new_arg (args) << "-L" << php_path << "/lib";
	new_arg (args) << "-Wl,-R" << php_path << "/lib";
	new_arg (args) << "-lphp5";
	new_arg (args) << "-xc";
	new_arg (args) << "-";

	// Add (gcc) -g and -o arguments
	if (strncmp (pm->args_info->optimize_arg, "0", 2) == 0)
	{
		new_arg (args) << "-ggdb3";
		new_arg (args) << "-O0";
	}
	else
	{
		// Use the specified optimization level
		new_arg (args) << "-O" << pm->args_info->optimize_arg;

		new_arg (args) << "-DNDEBUG"; // turn off assertions
		new_arg (args) << "-g"; // We still need this to profile
	}

	// add -C arguments
	for(unsigned i = 0; i < pm->args_info->c_option_given; i++)
		new_arg (args) << pm->args_info->c_option_arg[i]; 

	// add -o argument
	if (pm->args_info->output_given)
	{
		new_arg (args) << "-o" << pm->args_info->output_arg;
	}


	// copy it into argument list
	char** argv;
	argv = (char**) calloc(args.size ()+ 1, sizeof(char*));
	for(unsigned int i = 0; i < args.size (); i++) 
		argv[i] = strdup(args[i]->str().c_str());

	if(pm->args_info->verbose_flag)
	{
		for(unsigned int i = 0; i < args.size (); i++)
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
		cout << os.str ();
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

