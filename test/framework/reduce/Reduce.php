<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Automatically reduce test cases using phc and delta-debugging.
 */



/*
 * Introduction:
 *
 * The reduce class automatically reduces PHP test cases quickly (using the
 * delta-debugging algorithm). Given an input program, it will remove as many
 * statements as it can, checking for each statement that the bug is not
 * removed. It uses callbacks to check that the bug is not removed, so it is
 * flexible to nearly any problem.
 *
 * Usage:
 *
 *
 *		$filename = "test_case.php";
 *		$test_prog = file_get_contents ($filename);
 *		try
 *		{
 *			$reduce = new Reduce ();
 *			$reduce->set_checking_function ("my_checking_function");
 *			$reduced_prog = $reduce->run_on_php ($test_prog);
 *
 *			file_put_contents ("$filename.reduced", $reduced_prog);
 *		}
 *		catch (ReduceException e)
 *		{
 *			...
 *		}
 *
 *		function my_checking_function ()
 *		{
 *		   $bug_kept_in = (bool)(...);
 *		   return $bug_kept_in;
 *		}
 *
 *	Options:
 *	
 *		The basic usage is described above. But it can be tailored through a number of methods:
 *
 *			- set_checking_function ($callback)
 *				Set the function used for checking if the reduce step was
 *				successful. Its parameters are:
 *					$program - the PHP program to check
 *				It returns true if the redcue step was successful (ie if the bug
 *				was kept in), false otherwise.
 *
 *			- set_run_command_function ($callback)
 *				Set the function used for running shell commands. Its parameters are:
 *					$command - the command to be run
 *					$stdin - the input to it
 *				It should return false for failure, else it should return
 *					array ($stdout, $stderr, $exit_code)
 *				If this function is not provided, an exception will be thrown
 *
 *
 *		The following functions are more-or-less required, though you can survive without them.
 *
 *			- set_debug_function ($callback)
 *				Set the function used for debug messages. Its parameters are:
 *					$level - 0-3 representing importance of message (lower is better)
 *					$message - string message
 *				Its return value is ignored.
 *				If this function is not provided, print() will be used.
 *
 *			- set_dump_function ($callback)
 *				Set the function used for dumping intermediate files. Its parameters are:
 *					$level - 0-3 representing importance of message (lower is better)
 *					$message - string message
 *				Its return value is ignored.
 *				If this function is not provided, nothing will happen.
 *
 *
 *
 *		These methods are optional.
 *
 *			- set_comment ($comment);
 *				Add a comment to top of the reduced program
 *				If the comment is not called, no comment will be added.
 *
 *
 *		phc is required for usage. To set phc's configuration, use
 *
 *			- set_phc ($phc)
 *				Set the location of the phc executable
 *				Defaults to "phc" (ie using the PATH)
 *
 *			- set_plugin_path ($path)
 *				Set the path used by phc's plugins
 *				Defaults to "."
 *
 *
 */






# This attempts to reduce a test case to a minimal test case. For a
# program of N statements, it attempts to reduce it by N/2 statements
# chunks, then by N/4 statement chunks, and so on, while the progrmam
# still fails. 

# Complexity:
# TODO Actually, this is wrong, since each term has a larger
# complexity, because of k.
#
# There are N - K possible chunks for chunk size K. The number of
# iterations is (N-N/2) + (N-N/4) + ... + (N-1), which is log_2(N)
# steps of size N (the second term converges to N, so we discard it).
# So the number of iterations is O (N log N).  Each iteration leads to
# a traversal of each statement, giving worst case complexity of O
# (N^2 log N).


# Approach:
#	
# prog = input_file
# N = num_statements (prog)
# for each k = N/2; k > 0; k /=2
#	for each i = 0; i < N -k; i++
#   new_prog = prog.reduce (i, k)
#   if (reduce_successful (new_prog))
#    prog = new_prog
#    goto start;

class ReduceException extends Exception
{
	function __construct ($message)
	{
		Exception::__construct ($message);
	}
}

class Reduce
{
	function __construct ()
	{
		// defaults
		$this->set_phc ("phc");
		$this->set_pass ("AST-to-HIR");
		$this->set_plugin_path (".");
	}

	/*
	 * Methods to set configuration
	 */

	function set_comment ($comment)
	{
		$this->comment = $comment;
	}

	function set_plugin_path ($plugin_path)
	{
		$this->plugin_path = $plugin_path;
	}

	function set_run_command_function ($callback)
	{
		$this->run_command_function = $callback;
	}

	function set_debug_function ($callback)
	{
		$this->debug_function = $callback;
	}

	function set_dump_function ($callback)
	{
		$this->dump_function = $callback;
	}

	function set_pass ($passname)
	{
		$this->pass = $passname;
	}

	function set_checking_function ($callback)
	{
		$this->checking_function = $callback;
	}

	function set_phc ($phc)
	{
		$this->phc = $phc;
	}

	/*
	 * User-overridable utility methods
	 */

	function debug ($level, $message)
	{
		// Call a user-providec debug function, if provided
		if (isset ($this->debug_function))
		{
			call_user_func ($this->debug_function, $level, $message);
		}
		else
		{
			$this->warn_once ("Warning: no user-defined debug() function provided. Consider "
					."adding one via set_debug_function ()");

			print "$level: $message\n";
		}
	}

	// Returns array ($stdout, $stderr, $exit_code)
	function run_command ($command, $stdin = NULL)
	{
		if (isset ($this->run_command_function))
		{
			$result = call_user_func ($this->run_command_function, $command, $stdin);

			// Check the result
			if (	is_array ($result)
				&& count ($result) == 3
				&& is_string ($result[0])
				&& is_string ($result[1])
				&& is_numeric ($result[2]))
				return $result;
			else
				throw new ReduceException ("Result of run_command function has the wrong structure");
		}
		else
		{
			$this->warn_once ("Warning: no user-defined run_command () function provided. Consider "
					."adding one via set_run_command_function ()");

			throw new ReduceException ("No run_command function provided");
		}
	}

	function warn_once ($message)
	{
		static $cache = array ();
		if (isset ($cache[$message]))
			return;

		$cache[$message] = true;
		trigger_error (E_WARNING, $message);
	}


	function dump ($suffix, $output)
	{
		// Call a user-providec dump function, if provided
		if (isset ($this->dump_function))
		{
			call_user_func ($this->dump_function, $suffix, $output);
		}
		else
		{
			$this->warn_once ("Warning: no user-defined dump() function provided. Consider "
					."adding one via set_dump_function ()");
		}
	}


	function check ($program)
	{
		if (isset ($this->checking_function))
		{
			return call_user_func ($this->checking_function, $program);
		}
		else
		{
			throw new ReduceException ("No checking function present - add one using set_checking_function ()");
		}
	}



	/*
	 * Methods used as part of the algorithm
	 */

	function add_comment ($xprogram)
	{
		if (!isset ($this->comment))
			return $xprogram;

		$this->debug (2, "Adding comment");

		$command =   "{$this->phc} "
						."--read-xml={$this->pass} "
						."--run={$this->plugin_path}/plugins/tools/add_comment.la "
						."--r-option=\"Reduced by: $this->comment\" "
						."--dump-xml={$this->plugin_path}/plugins/tools/add_comment.la ";

		return $this->run_safe ($command, $xprogram);
	}

	function reduce_step ($xprogram, $start, $num)
	{
		$this->debug (2, "Reducing");
		$out = $this->run_safe (
			"$this->phc"
			." --read-xml=$this->pass"
			." --run=$this->plugin_path/plugins/tools/reduce_statements.la"
			." --r-option=$start:$num"
			." --dump-xml=$this->plugin_path/plugins/tools/reduce_statements.la",
			 $xprogram);

		return $out;
	}

	function convert ($xprogram, $upper)
	{
		$this->debug (2, "Converting to PHP from XML");
		$command =   "$this->phc"
						." --read-xml=$this->pass"
						." --dump=$this->pass";

		if ($upper && $this->pass == "mir")
		{
			$this->debug (2, "Uppering");
			$command .= " --convert-uppered";
		}

		return $this->run_safe ($command, $xprogram);
	}

	function count_statements ($xprogram)
	{
		$this->debug (2, "Counting statements");

		$out = $this->run_safe (
			"{$this->phc}"
				. " --read-xml={$this->plugin_path}/plugins/tutorials/count_statements_easy.la"
				. " --run={$this->plugin_path}/plugins/tutorials/count_statements_easy.la"
			, $xprogram);

		$this->debug (2, "Output is: $out");

		if (!preg_match ("/(\d+) statements found/", $out, $matched))
			throw ReduceException ("No statement string found");


		return $matched[1];
	}

	function has_syntax_errors ($program)
	{
		$this->debug (2, "Checking syntax errors");
		list ($out, $err, $exit) = $this->run_command ("php -l", $program);

		if ($exit || $err) // if the reduced case causes a PHP error, ignore.
		{
			$this->debug (1, "Syntax error detected: Skip. (out: $out, exit code: $exit, error: $err)");
			return true;
		}

		return false;
	}


	/* Check outputs */
	function run_safe ($command, $stdin = NULL)
	{
		list ($out, $err, $exit) = $this->run_command ($command, $stdin);

		if ($exit !== 0 || $err !== "")
			throw new ReduceException ("Error ($exit): $err");

		return $out;
	}


	# Reduce and test the program, passed as XML in $xprogram. Reduce it
	# starting from the $start'th statement, by $num statements. Return false if
	# the program couldnt reduce, or couldnt be tested, or the reduced program
	# otherwise.
	function do_main_step ($xprogram, $start, $num)
	{
		$this->num_steps++;

		# Reduce
		$this->debug (1, "Attempting to reduce by $num statements, starting at statement $start");
		$xnew_program = $this->reduce_step ($xprogram, $start, $num);
		$pnew_program = $this->convert ($xnew_program, 0); // converted to PHP
		$unew_program = $this->convert ($xnew_program, 1); // uppered

		$id = "{$num}_$start";
		$this->dump ("xreduced_$id", $xnew_program);
		$this->dump ("preduced_$id", $pnew_program);
		$this->dump ("ureduced_$id", $unew_program);

		if ($xprogram == $xnew_program && $num != 0)
		{
			// this would happen if we dont remove any statements
			// if $num == 0, then this is intentional
			$this->debug (1, "The two programs are identical. Skip.");
			return false;
		}

		if ($this->has_syntax_errors ($unew_program))
			return false;


		// Check if the new program is successful (has kept the bug in)
		if ($this->check ($unew_program))
		{
			$this->debug (2, "Success, bug kept in");
			$this->dump ("xsuccess_$id", $xnew_program);
			$this->dump ("psuccess_$id", $pnew_program);
			$this->dump ("usuccess_$id", $unew_program);
			return $xnew_program;
		}

		$this->debug (2, "Bug removed. Skip.");
		return false;
	}

	/* 
	 * The reduction algorithm itself
	 */
	function run_on_php ($program)
	{
		$this->debug (2, "Getting initial XML input");

		$command = "{$this->phc} --dump-xml=$this->pass";
		$out = $this->run_safe ($command, $program);

		if (substr ($out, 0, 5) != "<?xml")
			throw new ReduceException ("Cannot convert input file into XML: $out");

		return $this->run_on_xml ($out);
	}

	function run_on_xml ($xprogram)
	{
		$this->num_steps = 0;

		$N = $this->count_statements ($xprogram);

		$original = $N;
		$this->debug (1, "$N statements");

		if ($N == 0)
			throw new ReduceException ("No statements found");


		# confirm that we can find the bug automatically
		if (!$this->do_main_step ($xprogram, 0, 0))
			throw new ReduceException ("Program does not appear to have a bug");


		for ($k = (int)($N/2); $k >= 1; $k = (int)($k/2))
		{
			// RESTART:
			for ($i = 0; $i <= ($N-$k); $i += $k)
			{
				$result = $this->do_main_step ($xprogram, $i, $k);
				if ($result !== false)
				{
					$xprogram = $result;
					$N = $this->count_statements ($xprogram);
					$k = $N; // the iteration will divide $N by 2
					$this->debug (1, "Success, program reduced to $N statements");
					$this->debug (1, ""); // put a blank line in the debug
					continue 2;
				}
				$this->debug (1, ""); // put a blank line in the debug
			}
		}

		// we're done, it wont reduce any further
		$this->debug (0, "Reduced from $original to $N statements in $this->num_steps steps.");

		$xprogram = $this->add_comment ($xprogram);
		$pprogram = $this->convert ($xprogram, 0); // converted to PHP

		$this->dump ("reduced", $pprogram);
		$this->dump ("xreduced", $xprogram);

		return $pprogram;
	}
}


