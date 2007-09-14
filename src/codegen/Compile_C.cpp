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
	int num_args = 12 + pm->args_info->c_option_given + pm->args_info->output_given;
	stringstream** args = new stringstream* [num_args];
	int a = 0;
	for (int i = 0; i < num_args; i++)
	{
		args[i] = new stringstream();
	}
	*args[a++] << "gcc";
	*args[a++] << "-I" << php_path << "/include/php";
	*args[a++] << "-I" << php_path << "/include/php/main";
	*args[a++] << "-I" << php_path << "/include/php/TSRM";
	*args[a++] << "-I" << php_path << "/include/php/Zend";
	*args[a++] << "-L" << php_path << "/lib";
	*args[a++] << "-Wl,-R" << php_path << "/lib";
	*args[a++] << "-lphp5";
	*args[a++] << "-xc";
	*args[a++] << "-ggdb3";
	*args[a++] << "-O0";
	*args[a++] << "-";

	// add -C arguments
	for(unsigned i = 0; i < pm->args_info->c_option_given; i++)
		*args[a++] << pm->args_info->c_option_arg[i]; 

	// add -o argument
	if (pm->args_info->output_given)
	{
		*args [a++] << "-o" << pm->args_info->output_arg;
	}


	// copy it into argument list
	char** argv;
	argv = (char**) calloc(num_args + 1, sizeof(char*));
	for(int i = 0; i < num_args; i++) 
		argv[i] = strdup(args[i]->str().c_str());

	if(pm->args_info->verbose_flag)
	{
		for(int i = 0; i < num_args; i++)
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

