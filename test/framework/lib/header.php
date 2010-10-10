<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Some standard functions
 */

function get_phc ()
{
	global $opt_valgrind, $phc_suffix, $valgrind, $libphp, $working_dir;

	// first check that this isnt being run from the wrong directory
	// (the right directory contains ./phc - if you get this far you
	// have the tests)
	$phc = "src/phc$phc_suffix";
	if (!(file_exists($phc) and is_file($phc) and is_executable($phc)))
	{
		$cwd = getcwd ();
		die ("Error: The current directory, $cwd, does not contain the phc executable '$phc'\n");
	}


	// now copy to the working directory, so we can safely compile
	// the executable while the tests run.
	$phc = copy_to_working_dir ($phc);

	if ($opt_valgrind)
	{
		if (!$valgrind) die ("Error: Valgrind not available (see output from ./configure)\n");
		# we turn off the leak check because we dont tidy up any garbage
		$phc = "$valgrind -q --suppressions=misc/valgrind_suppressions --leak-check=no $phc";
	}
	return $phc;

}

function get_phc_compile_plugin ()
{
	// first check that this isnt being run from the wrong directory (the right directory contains ./phc - if you get this far you have the tests)
	$phc_compile_plugin = "src/phc_compile_plugin";
	if (!file_exists($phc_compile_plugin) and is_file($phc_compile_plugin) and is_executable($phc_compile_plugin))
	{
		$cwd = getcwd ();
		die ("Error: The current directory, $cwd, does not contain the phc executable '$phc'\n");
	}

	$phc_compile_plugin = copy_to_working_dir ($phc_compile_plugin);

	return $phc_compile_plugin;

}

function get_php ()
{
	global $php_exe;

	# use the version of PHP found by configure
	if ($php_exe)
	{
		# remember this screipt si running with the same php we will be using
		if (PHP_SAPI == "cgi")
		{
			return "$php_exe -Cq -d html_errors=0";
		}

		return "$php_exe -C";
	}
	else
	{
		$php = trim (`which php`);
		return "$php -C";
	}
}

// For a pipe, just put a blank $subject
function get_php_command_line ($subject, $pipe = false)
{
	phc_assert ($subject != "", "dont pass empty subject, even for pipe");

	global $php;
	global $opt_long;

	if ($opt_long)
		$max_exe = 12;
	else
		$max_exe = 5;

	$dir_path = dirname($subject);
	if ($pipe) $subject = ""; # we need the subject for the dir_name
	return "$php -d include_path=./:test/subjects/:$dir_path -d max_execution_time=$max_exe $subject ";
}

function get_phc_command_line ($subject)
{
	phc_assert ($subject != "", "dont pass empty subject");

	global $phc;
	global $opt_long;

	if ($opt_long)
		$max_exe = 12;
	else
		$max_exe = 5;

	$dir_path = dirname($subject);
	return "$phc -d include_path=./:test/subjects/:$dir_path -d max_execution_time=$max_exe $subject ";
}



// Get a subject in the forms "test/subjects/codegen/000.php.out", and return "test_subjects_codegen_000.php.out"
function wd_name ($subject)
{
	global $working_directory;
	return "$working_directory/". preg_replace ("/\//", "_", $subject);
}


$strict = false;
function phc_error_handler ($errno, $errstr, $errfile, $errline, $errcontext)
{
	global $strict;
	if (error_reporting() == 0) return; // means the @ suppression was used
	if ($errno === E_STRICT && $strict == false) return;
	if ($errno === E_WARNING && $strict == false) return;
	if ($errno === E_USER_WARNING && $strict == false) return;

	$red = red_string ();
	$reset = reset_string();
	$blue = blue_string();

	print "\n$red-----Error----------$reset\n";

	print "\n$red----Context---------$reset\n";
	$long_dump = "";
	foreach ($errcontext as $name => $context)
	{
		$long_dump .= sprintf("$blue$%-12s$reset => ", $name);
		$dump = preg_replace ("/\n/", " ", print_r($context, true));
		$long_dump .= "$dump; $reset\n";
	}
	if (strlen ($long_dump) > 640)
	{
		print "{$red}Context skipped, too long (" .strlen($long_dump).")";
	}
	else
	{
		print $long_dump;
	}
	print "\n";

	print "\n$red----Backtrace-------$reset\n";
	$backtrace = debug_backtrace ();
	$prev_frame = $backtrace[0];

	$j = 0; // use j for printing
	/* skip listing this function */
	for ($i = 1; $i < count($backtrace); $i++)
	{
		$frame = $backtrace[$i];
		$function = $frame{"function"};
		$object = $frame{"object"};
		$class = @get_class($frame{"object"});
		$type = $frame{"type"};

		/* skip trigger_error and multiple asserts */
		if (($function == "trigger_error")
				or ($function == "phc_assert" 
					and
					$backtrace[$i+1]{"function"} == "phc_unreachable"))
		{
			$prev_frame = $frame;
			continue;
		}


		/* make the arg string readable */
		$args = $frame{"args"};
		if ($args == NULL) $args = array (); // sometimes args is NULL
		foreach ($args as &$arg) // cant convert objects to strings
		{
			if (is_object ($arg))
				$arg = "OBJECT";
		}
		$args_string = join(", ", $args);
		$args_string = preg_replace ("/\n/", "", $args_string);
		$args_string = substr ($args_string, 0, 30);
		if (strlen ($args_string) == 30) 
			$args_string .= "...";

		/* print the frame info */
		if ($prev_frame === NULL)
		{
			print "#$j $class$type$function ($args_string)\n";
		}
		else
		{
			$file = $prev_frame{"file"};
			$file = preg_replace ("!^.*/framework/(.*$)!", "$1", $file);
			$line = $prev_frame{"line"};
			print "#$j $class$type$function ($args_string) at $file:$line\n";
		}
		$prev_frame = $frame;
		$j++;
	}

	/* print the final frame */
	$file = $prev_frame{"file"};
	$file = preg_replace ("!^.*/framework/(.*$)!", "$1", $file);
	$line = $prev_frame{"line"};
	print "#$j called from $file:$line\n";


	print "\n$red----Message---------$reset\n";
	die(sprintf ("Error ($errno): '$errstr' at $errfile:$errline\n"));
}
set_error_handler ("phc_error_handler");

$status_file_names = array ("failure", "skipped", "success", "timeout", "results", "pure", "impure");
function open_status_files ()
{
  global $status_file_names, $status_files, $log_directory;
	foreach ($status_file_names as $status)
	{
		$status_files[$status] = fopen ("$log_directory/$status", "w") or die ("Cannot open $status file\n");
	}
}

function log_status ($status, $test_name, $subject, $reason)
{
	$status_name = ucfirst ($status);
	if ($reason != "") $reason = " - $reason";
	write_status ($status, "$test_name: $status_name $subject$reason\n");
}

function write_status ($status, $string)
{
	global $status_files;
	$file = $status_files[$status];

	fwrite ($file, $string);

	// we frequently stop the test midway, but we want up to the minute results
	fflush ($file);
}

function close_status_files ()
{
	global $status_files;
	foreach ($status_files as $file)
		fclose ($file);

	// Sort them
	global $log_directory, $status_file_names;
	foreach ($status_file_names as $filename)
	{
    $log_file = "$log_directory/$filename";
    $lines = file_get_contents($log_file);
    $lines = explode("\n", $lines);
    sort ($lines, SORT_STRING);
    $lines = implode("\n", $lines);
		file_put_contents($log_file, $lines);
	}
}

// $matches means the command line arguments, which are regexes.
// $quick means only the top 10 files are used, so ignore the '-'s.
function diff_status_files ($matches = array(), $quick=false)
{
	print "Comparing to expected:\n";
 
	global $log_directory;
	foreach (array("failure", "skipped", "success", "timeout") as $status)
	{
		$log_file = "$log_directory/$status";
		$expected_file = "test/expected_results/$status";

		$cmd = "diff $expected_file $log_file -U 0";

		if ($quick)
		{
			$cmd .= ' | grep -v \'^-\'';
		}
		$result = `$cmd`;
		$result = preg_split ('/\n/', $result);

		if (count ($matches))
		{
			$output = array();
			foreach ($result as $line)
			{
				foreach ($matches as $match)
				{
					if (preg_match ("/$match/", $line))
					{
						$output[] = $line;
						break;
					}
				}
			}
			$result = $output;
		}
		$result = join("\n", $result);
		print "$result\n";
	}
}



function phc_assert ($boolean, $message)
{
	if (!$boolean)
	{
		trigger_error ($message);
	}
}

function phc_unreachable ($message = "This point should be unreachable")
{
	phc_assert (false, $message);
}

function reset_string()
{
	return sprintf("%c[0m", 27);
}

// blue foreground color 
function blue_string()
{
	return sprintf("%c[1;34m", 27);
}

// green foreground color 
function green_string()
{
	return sprintf("%c[1;32m", 27);
}

// red foreground color 
function red_string()
{
	return sprintf("%c[1;31m", 27);
}

function strip_colour	($string)
{
	$codes = array (red_string (), green_string (), blue_string (), reset_string ());
	return str_replace ($codes, "", $string);
}


// returns true if the machine is 32 bit (based on integer arithmetic)
function is_32_bit()
{
	# 2147483648 == 2^31
	if (is_integer(2147483648  + 10)) # this should convert to a real on a 32 bit machine
	{
		return false;
	}
	return true;
}

/* Prints diffs if the xdiff extension is available, and simple outputs both
 * strings otherwise. 
 * To install xdiff:
 *   install libxdiff from http://www.xmailserver.org/xdiff-lib.html 
 *   install xdiff from pecl with "pecl install xdiff". 
 *   There is no need to load xdiff.so in your php.ini file. */
function diff ($string1, $string2)
{
	if (!extension_loaded ("xdiff"))
	{
		$result = @dl ("xdiff.so"); // avoid the E_WARNING
		if (!$result)
		{
			return "Note: xdiff not available for diffing. Outputting both strings:\nString1:\n$string1\nString2:\n$string2";
		}
	}

	if (strlen ($string1) > 5000000 || strlen ($string2) > 5000000)
		return "Too big to xdiff. Outputting both strings:\nString1:\n$string1\nString2:\n$string2";

	return xdiff_string_diff ("$string1\n", "$string2\n");
}

function log_failure ($test_name, $subject, $commands, $outs, $errs, $exits, $missing_dependency, $reason)
{
	$red = red_string();
  $reset = reset_string();

	// I can't find where this comes from.
	if (count ($commands < count ($exits)))
		$commands[] = "Missing command";

	assert (count ($outs) == count ($errs));
	assert (count ($exits) == count ($errs));
	assert (count ($commands) == count ($errs));

	// We have 1 or more outputs, only 1 error, and 1 or more commands, with the
	// same number of error codes as commands
	$err_string = "";
	if (is_array ($commands))
	{
		if ($exits == "Not relevent")
		{
			$command_string = "";
			foreach ($commands as $command)
			{
				$command_string .= "{$red}Command:$reset $command\n";
			}
		}
		else
		{
			phc_assert (is_array ($exits), "Expected array of return values");
			phc_assert (count ($exits) == count ($errs), 
					"Expected same number of exits as exit codes");

			$command_string = "";
			$err_string = "";
			foreach ($exits as $i => $exit)
			{
				if (!isset ($commands[$i]))
				{
					var_dump ($outs, $exits, $commands, $errs);
					die ();
				}

				$command = $commands[$i];

				$err = $errs [$i];
				$command_string .= "{$red}Command $i$reset ($exit): $command\n";
				if ($err)
					$err_string .= "{$red}Error $i$reset: $err\n";
			}
		}

	}
	else
	{
		$command_string = "{$red}Command$reset ($exits): $commands\n";
		if ($errs)
			$err_string = "{$red}Error$reset: $errs\n";
	}

	$reason_string = "Reason: $reason\n";

	$dependency_string = "";
	if ($missing_dependency)
	{
		$dependency_string = "NOTE: dependency $missing_dependency is missing. This may be the cause of this failure\n";
	}

	$header = "$reason_string$dependency_string$command_string$err_string";

	// ready the output information
	global $log_directory;
	$script_name = adjusted_name ($subject);
	$filename = "$log_directory/$test_name/$script_name.log";
	$dirname = dirname($filename);
	if (!is_dir ($dirname))
	{
		@mkdir($dirname, 0755, true);
		phc_assert (is_dir($dirname), "directory not created");
	}


	if (!is_array ($outs))
		$outs = array ($outs);

	$out_string = "";
	// create the stdout logs - but only if there is more than 1 log
	if (count ($outs) > 1 && count (array_filter ($outs, "strlen")))
	{
		foreach ($outs as $i => $out)
		{
			$output_contents = "Command: ${commands[$i]}\n" . $out;
			file_put_contents ("$filename.out.$i", $output_contents);
		}
	}

	// write to the main log file
	foreach ($outs as $i => $out)
	{
		if (strlen ($out) > 1000)
			$out = substr ($out, 0, 1000) . "... [truncated]\n";

		$out_string .= "{$red}Output $i$reset:\n$out\n";
	}

	// print the output
	file_put_contents($filename, $header);
	file_put_contents($filename, rtrim($out_string), FILE_APPEND);
	file_put_contents($filename, "\n", FILE_APPEND);
}

function adjusted_name ($script_name, $adjust_for_regression = 0)
{
	global $subject_dir;
	phc_assert($subject_dir !== "", "subject_dir must be defined before this function is called");

	// we need the prefix for the check
	if($adjust_for_regression)
	{
		// add the size-dependent suffix
		if (is_labelled($script_name, "size-dependent"))
		{
			if(is_32_bit())
			{
				$script_name .= ".32bit";
			}
			else
			{
				$script_name .= ".64bit";
			}
		}
	}

	// remove the prefix
	$prefix = $subject_dir;
	$prefix = preg_replace("/\//", "\\/", $prefix);
	$script_name = preg_replace("/$prefix/", "", $script_name);

	return $script_name;
}

function complete_exec($command, $stdin = NULL, $timeout = 20, $pass_through = false)
{
	global $opt_verbose;
	if ($opt_verbose)
		print "Running command: $command\n";

	$descriptorspec = array(0 => array("pipe", "r"),
									1 => array("pipe", "w"),
									2 => array("pipe", "w"));
	$pipes = array();
	$handle = proc_open($command, $descriptorspec, $pipes, getcwd());
	
	# read stdin into the process
	if ($stdin !== NULL)
		fwrite ($pipes[0], $stdin);

	fclose ($pipes[0]);
	unset ($pipes[0]);

	// set non blocking to avoid infinite loops on stuck programs
	stream_set_blocking ($pipes[1], 0);
	stream_set_blocking ($pipes[2], 0);

	$out = "";
	$err = "";

	$start_time = time ();
	do
	{
		$status = proc_get_status ($handle);

		// It seems that with a large amount fo output, the process
		// won't finish unless the buffers are periodically cleared.
		// (This doesn't seem to be the case is async_test. I don't
		// know why).
		$new_out = stream_get_contents ($pipes[1]);
		$new_err = stream_get_contents ($pipes[2]);
		$out .= $new_out;
		$err .= $new_err;

		if ($pass_through)
		{
			print $new_out;
			file_put_contents ("php://stderr", $new_err);
		}

		if ($timeout != 0
			&& time () > $start_time + $timeout)
		{
			$out = stream_get_contents ($pipes[1]);
			$err = stream_get_contents ($pipes[2]);

			kill_properly ($handle, $pipes);

			return array ("Timeout", $out, $err);
		}

		// Since we use non-blocking, the for loop could well take 100%
		// CPU. time of 1000 - 10000 seems OK. 100000 slows down the
		// program by 50%.
		usleep (10000);
	}
	while ($status["running"]);
	stream_set_blocking ($pipes[1], 1);
	stream_set_blocking ($pipes[2], 1);
	$out .= stream_get_contents ($pipes[1]);
	$err .= stream_get_contents ($pipes[2]);

	$exit_code = $status["exitcode"];
	
	kill_properly ($handle, $pipes);

	return array ($out, $err, $exit_code);
}

# Kill the process, and close the pipes.
function kill_properly (&$handle, &$pipes)
{
	$status = proc_get_status ($handle);

	# proc_terminate kills the shell process, but won't kill a runaway infinite
	# loop. Get the child processes using ps, before killing the parent.
	$ppid = $status["pid"];
	$pids = preg_split ("/\s+/", trim (`ps -o pid --no-heading --ppid $ppid`));

	# if we dont close pipes, we can create deadlock, leaving zombie processes.
	foreach ($pipes as &$pipe) fclose ($pipe);
	proc_terminate ($handle);
	proc_close ($handle);

	// Not necessarily available.
	if (function_exists ("posix_kill"))
	{
		foreach ($pids as $pid)
		{
			if (is_numeric ($pid))
				posix_kill ($pid, 9);
		}
	}
}

function check_for_plugin ($plugin_name)
{
	global $plugin_dir;
	return file_exists ("$plugin_dir/$plugin_name.la");
}

function check_for_program ($program_name)
{
	// only use the first word
	$program_names = explode (" ", $program_name);
	$program_name = $program_names[0];

	return ($program_name !== "" 
			&& (file_exists ($program_name) or $program_name == "gcc"));
}

function date_string ()
{
	# only generate once
	# Day_date_month_hour_min_sec
	global $date_string;
	if ($date_string == NULL)
	{
		$date_string = date ("D_d_M_H_i_s");
	}

	return $date_string;

}

/* These are used to store dependencies. When a test is run, we dont want to
 * display errors for tests which we know will fail, since they failed a
 * previous test, and are guaranteed to fail this one. I tried a number of
 * other approaches to this, including keeping a single set of results in a
 * file, or a file per test run, or a file per test, and they all had flaws.
 * 
 * There are a number of odd problems. First, any number of tests can be run,
 * and you can run a test without running its dependencies, and it is desirable
 * to do so. Secondly, a test run can stop at any point, due to an exit or a
 * CTRL-C. Thirdly, multiple test runs can occur simulateously, and shouldnt
 * interfere with each other. In all these cases, incorrect behaviour can lead
 * to dependencies being incorrectly guessed, or overwritten with incorrect
 * information, or not available at all. This will result in people searching
 * for bugs in the wrong places, or not being able to identify actual bugs.
 *
 * The final chosen solution is to have a single directory (test/dependecnies/),
 * containing one directory for each test, and each of these containing 1 file
 * per test subject. The contents of this file is "Pass" or "Fail". The file is
 * read each time we want to resolve a dependency, and never cached. 
 *
 * If the file doesnt exist, then we cant resolve the dependency, which works
 * out the same as a "Pass", in that dependent tests will run. This is the only
 * time we can get incorrect information. In this case, we mark the failure
 * log, so that we dont go on wild goose chases without being told.
 */

function get_dependent_filename ($test_name, $subject)
{
	$result = "test/dependencies/$test_name/$subject";

	// make sure the directory exists
	if (!file_exists (dirname ($result)))
	{
		$is_made = mkdir (dirname ($result), 0700, true);
		assert ($is_made);
	}

	return $result;
}
function write_dependencies ($test_name, $subject, $value)
{
	$filename = get_dependent_filename ($test_name, $subject);
	if ($value == true)
	{
		file_put_contents ($filename, "Pass");
	}
	else
	{
		file_put_contents ($filename, "Fail");
	}
}

function read_dependency ($test_name, $subject)
{
	$filename = get_dependent_filename ($test_name, $subject);
	if (!file_exists ($filename))
		return "missing";
	else
		return file_get_contents ($filename);
}



function homogenize_xml ($string)
{
	$string = preg_replace("/(<attr key=\"phc.line_number\">)\d+(<\/attr>)/", "$1$2", $string);
	$string = preg_replace("/(<attr key=\"phc.filename\">).*?(<\/attr>)/", "$1$2", $string);

	// fresh doesnt return the same numbers every time.
	$string = preg_replace("/(<value>\D+)\d+(<\/value>)/", "$1xx$2", $string);
	$string = preg_replace("/(<string>\D+)\d+(<\/string>)/", "$1xx$2", $string);
	return $string;
}

function homogenize_filenames_and_line_numbers ($string, $filename)
{
	global $base_dir;

	// This doesnt work for install tests.
	$stdin_filename = "$base_dir/-";
	$full_filename = "$base_dir/$filename";


	// Remove 'Unknown:'
	$string = preg_replace( "/Warning: Unknown:/", "Warning:", $string);
	$string = preg_replace( "/fatal error: Unknown:/", "Fatal error:", $string);
	$string = preg_replace( "/Catchable fatal error: Unknown:/", "Catchable fatal error:", $string);


	// Sometimes there is a filename, sometimes not. Easiest to leave as is,
	// rather than trying to coerce __FILENAME__ into it.
	$string = preg_replace( "/(Warning: )(\S*: )?(.+? in )\S+ on line \d+/", "$1$3", $string);
	$string = preg_replace( "/(Fatal error: )(\S*: )?(.+? in )\S+ on line \d+/", "$1$3", $string);
	$string = preg_replace( "/(Catchable fatal error: .+? in )\S+ on line \d+/", "$1", $string);

	$string = preg_replace( "/on line \d+/", "on line __LINE__", $string);
	$string = preg_replace( "!$full_filename(:\d+)?!", "__FILENAME__", $string);
	$string = preg_replace( "!\[no active file\](:\d+)?!", "__FILENAME__", $string);
	$string = preg_replace( "!$filename(:\d+)?!", "__FILENAME__", $string);
	$string = preg_replace( "!$stdin_filename(:\d+)?!", "__FILENAME__", $string);

	$string = preg_replace( "!__FILENAME__ on line __LINE__!", "", $string);

//	$string = preg_replace( "/(Fatal error: Allowed memory size of )\d+( bytes exhausted at )\S*( \(tried to allocate )\d+( bytes\) in )\S*( on line )\d+/", "$1$2$3$4", $string);

	return $string;
}

function homogenize_break_levels ($string)
{
	// this is a bug we want to ignore
	$string = preg_replace( "/(Fatal error: Cannot break\/continue 1 level)s/", "$1", $string);
	return $string;
}

// This strips off the & from a var_dump. Changing whether something
// is a reference or not isnt correct, but changing the refcount is
// ok. If a var only has a reference count of 1, then is_ref wont be
// set, so the & wont be present.
function homogenize_reference_count ($string)
{
	// A var dump for an array looks like this:
	//		array(2) {
	//			["a"]=>
	//			&string(1) "a"
	//			["b"]=>
	//			string(1) "b"
	//		}
	$string = preg_replace(
		"/
			(\s+\[.*?\]=>\s+)		# key and newline
			&							# we want to delete this
			(.*?)						# dont go too far
		/Ssmx", "$1$2", $string); // s=DOTALL,m=MULTILINE,x=EXTENDED,S=STUDY(?)
	return $string;
}

/* We do not care if there is one object, or two objects alive at any point.
 * However, var_dump will give different results depending on the number of
 * live objects of a particular type. Since we shred, we make the extra objects
 * stay alive longer. So mask it from testing. */
function homogenize_object_count ($string)
{
	// A var dump for an object looks like this:
	# object(Foo)#1 (2) {
	#   ["x1"]=>
	#   string(8) "Foo::Bar"
	#   ["x2"]=>
	#   array(1) {
	#     [0]=>
	#     string(8) "Foo::Bar"
	#   }
	# }

	$string = preg_replace("/^(object\(\w+\)#)\d+/m", "$1x", $string);
	return $string;
}

function homogenize_all ($string, $filename)
{
	$string = homogenize_reference_count ($string);
	$string = homogenize_object_count ($string);
	$string = homogenize_filenames_and_line_numbers ($string, $filename);
	$string = homogenize_break_levels ($string);
	return $string;
}

function copy_to_working_dir ($file)
{
	# I'm fairly sure this doesn't work properly since we libtool'ed up. To fix 
	# it, we'd need to copy the .libs directory, and make sure the bash scripts 
	# that libtool sets up instead of phc have all their dependencies set right.
	return $file;


	global $working_directory;
	$filename = basename ($file);
	$new_file = "$working_directory/$filename";
	copy ($file, $new_file);
	chmod ($new_file, fileperms ($file));
	return $new_file;
}

function strip_console_codes ($string)
{
	// strip console codes
	$string = preg_replace("/\[1;\d\dm/", "", $string);
	$string = preg_replace("/\[0m/", "", $string); 
	return $string;
}



?>
