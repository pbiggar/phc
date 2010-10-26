/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compile generated C code
 */

#include <sstream>
#include <iostream>
#include <string.h>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <lib/error.h>
#include <lib/Vector.h>

#include "Compile_C.h"
#include "pass_manager/Pass_manager.h"

using namespace std;

Compile_C::Compile_C (stringstream& os)
: os(os)
{
	this->name = new String ("compile-c");
	this->description = new String ("Compile C code into an executable");
}

stringstream& new_arg (Vector<stringstream*> &args)
{
	stringstream* stream = new stringstream;
	args.push_back (stream);
	return *stream;
}

bool Compile_C::pass_is_enabled (Pass_manager* pm)
{
	return pm->args_info->compile_flag;
}

void Compile_C::run (IR::PHP_script* in, Pass_manager* pm)
{
	// Find PHP installation path
	const char* php_path;
	if(pm->args_info->with_php_given)
		php_path = pm->args_info->with_php_arg;
	else
	{
		#ifdef PHP_INSTALL_PATH
			php_path = PHP_INSTALL_PATH;
		#else
			phc_error ("PHP_INSTALL_PATH not configured. Please use the --with-php flag to compile");
			assert (0); // in the case of --dont-fail, still fail here.
		#endif
	}


	// Argument array for gcc
	Vector<stringstream*> args;
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

	// convert to a string in case of error
	stringstream command;
	for(unsigned int i = 0; i < args.size (); i++)
		command << argv[i] << " ";

	if(pm->args_info->verbose_flag)
	{
		cout << command.str () << endl;
	}

	// Pipe output of Generate_C into gcc
	int pfd[2];
	int error_pipe[2];
#define READ_END 0
#define WRITE_END 1
	if(pipe(pfd) == -1) 
		phc_error ("Could not create pipe");
	
	if (pipe (error_pipe) == -1)
		phc_error ("Could not create error pipe");

	int cpid = fork();
	if(cpid == -1)
		phc_error ("Could not fork");

	if(cpid == 0)
	{
		// Child (gcc)
		close(pfd[WRITE_END]);
		dup2(pfd[READ_END], STDIN_FILENO);
		
		close (error_pipe[READ_END]);
		dup2 (error_pipe[WRITE_END], STDERR_FILENO);

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

		close (error_pipe[WRITE_END]);

		// Output previously generated C
		cout << os.str ();
		cout.flush();

		// Close the pipe into indicate EOF to gcc
		close(STDOUT_FILENO);
		close(pfd[WRITE_END]);

		// Wait for gcc to finish (get the exit code)
		int exit_code;
		waitpid(cpid, &exit_code, 0);
		if (WEXITSTATUS (exit_code))
		{
			phc_error ("gcc exited with error %d (executed via '%s')", exit_code, command.str().c_str ());
		}

		FILE* stderr_file = fdopen (error_pipe[READ_END], "r");
		char buffer[100];
		buffer[0] = '\0';
		while (!feof (stderr_file))
		{
			fgets (buffer, 100, stderr_file);
			string s(buffer);
			if (s.substr (0, 32) == "<stdin>: In function ‘main’:")
			{
				char otherbuffer[100];
				fgets (otherbuffer, 100, stderr_file);
				string t(otherbuffer);
				if (t.substr (t.find_first_of ('w', 0) , 47) != "warning: useless type name in empty declaration")
				{
					cerr << buffer;
					cerr << otherbuffer;
				}	
			}
			else
				cerr << buffer;
		}

		// Restore stdout
		dup(old_stdout);
		close(old_stdout);
	}

   // TODO: allow options to be passed at compile-time, for this option.
   // There is a worry that this will interfere with the later plan to allow
   // compiling multiple files into a single extension with multiple entry
   // points, so make them mutually-exclusive when that happens.
   if (pm->args_info->execute_flag)
   {
      string exe_name = "a.out";
      if (pm->args_info->output_given)
         exe_name = pm->args_info->output_arg;

		// TODO what about an absolute path
		string executable = "./";
		executable.append (exe_name);

      int cpid = fork();
      if(cpid == -1)
         phc_error ("Could not fork");

      if(cpid == 0)
      {
         char* end_list = NULL;
         // Child (a.out)
         close(pfd[WRITE_END]);
         dup2(pfd[READ_END], STDIN_FILENO);
			errno = 0;
         execvp(executable.c_str(), &end_list);
			phc_error ("Error executing: %s", strerror (errno));
      }
      else
      {
         // Parent (phc)

         // Wait for the executable to finish (get the exit code)
         int exit_code;
         waitpid(cpid, &exit_code, 0);
         exit (exit_code);
      }
   }
}
