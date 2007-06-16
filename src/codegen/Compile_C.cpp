/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compile generated C code
 */

#include "codegen/Compile_C.h"
#include <dlfcn.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

Compile_C::Compile_C (stringstream& os)
: os(os)
{
	this->name = new String ("compile_c");
}

void Compile_C::run (AST_php_script* in, Pass_manager* pm)
{
	if (not pm->args_info->compile_flag)
		return;

	// Find PHP installation path
	char* php_path;
	if(pm->args_info->with_php_given)
		php_path = pm->args_info->with_php_arg;
	else
		php_path = PHP_INSTALL_PATH;

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
	argv = (char**) calloc(GCC_ARGS + pm->args_info->c_option_given + 1, sizeof(char*));
	for(unsigned i = 0; i < GCC_ARGS; i++) 
		argv[i] = strdup(args[i].str().c_str());
	for(unsigned i = 0; i < pm->args_info->c_option_given; i++)
		argv[GCC_ARGS + i] = pm->args_info->c_option_arg[i]; 
	argv[GCC_ARGS + pm->args_info->c_option_given] = NULL;

	if(pm->args_info->verbose_flag)
	{
		for(unsigned i = 0; i < GCC_ARGS + pm->args_info->c_option_given; i++)
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

