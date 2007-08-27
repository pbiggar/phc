<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Some standard functions
 */


function get_phc ()
{
	global $opt_valgrind, $phc_suffix, $valgrind, $libphp;

	// first check that this isnt being run from the wrong directory (the right directory contains ./phc - if you get this far you have the tests)
	$phc = "src/phc$phc_suffix";
	if (!file_exists($phc) and is_file($phc) and is_executable($phc))
	{
		$cwd = getcwd ();
		die ("Error: The current directory, $cwd, does not contain the phc executable '$phc'\n");
	}

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


$strict = false;
function phc_error_handler ($errno, $errstr, $errfile, $errline, $errcontext)
{
	global $strict;
	if (error_reporting() == 0) return; // means the @ suppression was used
	if ($errno === E_STRICT && $strict == false) return;

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
		$class = get_class($frame{"object"});
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

function open_status_files ()
{
	global $status_files;
	global $log_directory;
	foreach (array ("failure", "skipped", "success") as $status)
	{
		$status_files[$status] = fopen ("$log_directory/$status", "w") or die ("Cannot open $status file\n");
	}
}

function log_status ($status, $test_name, $subject, $reason = "")
{
	global $status_files;
	$file = $status_files[$status];

	if ($reason) $reason .= " - $reason";
	$status = ucfirst ($status);
	fprintf ($file, "%s", "$test_name: $status $subject$reason\n");

	// we frequently stop the test midway, but we want up to the minute results
	fflush ($file);
}

function close_status_files ()
{
	global $status_files;
	foreach ($status_files as $file)
		fclose ($file);
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
	return xdiff_string_diff ("$string1\n", "$string2\n");
}

function log_failure ($test_name, $subject, $header, $output)
{
	global $log_directory;
	$script_name = adjusted_name ($subject);
	$filename = "$log_directory/$test_name/$script_name.log";
	$dirname = dirname($filename);
	if (!is_dir ($dirname))
	{
		@mkdir($dirname, 0755, true);
		phc_assert (is_dir($dirname), "directory not created");
	}

	file_put_contents($filename, $header);
	file_put_contents($filename, rtrim($output), FILE_APPEND);
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

function complete_exec($command)
{
	global $opt_verbose;

	$descriptorspec = array(1 => array("pipe", "w"),
									2 => array("pipe", "w"));
	$pipes = array();
	$handle = proc_open($command, $descriptorspec, &$pipes);
	
	$out = "";
	$err = "";
	do
	{
		$out .= stream_get_contents ($pipes[1]);
		$err .= stream_get_contents ($pipes[2]);
		$status = proc_get_status ($handle);
	}
	while ($status["running"]);
	$out .= stream_get_contents ($pipes[1]);
	$err .= stream_get_contents ($pipes[2]);
	# contrary to popular opinion, proc_close doesnt return the exit
	# status
	$exit_code = $status["exitcode"];
	proc_close ($handle);
	if ($opt_verbose)
		print "Running: $command\n";
	return array ($out, $err, $exit_code);
}

function check_for_plugin ($plugin_name)
{
	global $plugin_dir;
	return file_exists ("$plugin_dir/$plugin_name.la");
}

function check_for_program ($program_name)
{
	// only use the first word
	$program_names = split (" ", $program_name);
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
 * The final chosen solution is to have a single directory (test/failures/),
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
	return $string;
}

function homogenize_filenames_and_line_numbers ($string)
{
	// specific errors and warnings
	$string = preg_replace( "/(Warning: ).*(\(\) expects the argument \(.*\) to be a valid callback in ).*( on line )\d+/" , "$1$2$3", $string);
	$string = preg_replace( "/(Fatal error: Cannot redeclare .*\(\) \(previously declared in ).*(:)\d+(\))/" , "$1$2$3", $string);
//	$string = preg_replace("/(Fatal error: Allowed memory size of )\d+( bytes exhausted at ).*( \(tried to allocate )\d+( bytes\) in ).*( on line )\d+/", "$1$2$3$4", $string);

	// general line number and filename removal
	$string = preg_replace( "/(Warning: .* in ).*( on line )\d+/", "$1$2", $string);
	$string = preg_replace( "/(Fatal error: )(.*: )?(.* in ).*( on line )\d+/", "$1$3$4", $string);
	$string = preg_replace( "/(Catchable fatal error: .* in ).*( on line )\d+/", "$1$2", $string);

	return $string;
}

function homogenize_break_levels ($string)
{
	// this is a bug we want to ignore
	$string = preg_replace( "/(Fatal error: Cannot break\/continue 1 level)s/", "$1", $string);
	return $string;
}

function homogenize_warnings ($string)
{
	# just clear these warnings
	$string = preg_replace(	"/Warning: Invalid argument supplied for foreach\(\) in/",
									"", $string);
	$string = preg_replace(	"/Warning: Variable passed to each\(\) is not an array or object in/",
									"", $string);
	return $string;
}

// its still correct if the number of references is off, so look for var_dump output, and remove &s from it
function homogenize_reference_count ($string)
{
# this only actually finds differences in arrays
	$string = preg_replace(
		"/
					(\s+\[.*?\]=>\s+)		# key and newline
					&							# we want to delete this
					(.*?\s+)					# dont go too far
		/smx", "$1$2", $string);
	return $string;
}

function homogenize_all ($string)
{
	$string = homogenize_reference_count ($string);
	$string = homogenize_warnings ($string);
	$string = homogenize_filenames_and_line_numbers ($string);
}



?>
