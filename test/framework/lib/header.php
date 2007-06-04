<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Some standard functions
 */

require_once ("autovars.php");
require_once ("startup.php");

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

function open_skipped_file ()
{
	global $skipped_file;
	global $log_directory;
	$skipped_file = fopen ("$log_directory/skipped", "w") or die ("Cannot open skipped file\n");
}

function note_in_skipped_file ($test_name, $subject, $reason)
{
	global $skipped_file;
	fprintf ($skipped_file, "%s", "$test_name: Skipped $subject - $reason\n");
	// we frequently stop the test midway, but we want up to the minute results
	fflush ($skipped_file);
}

function close_skipped_file ()
{
	global $skipped_file;
	fclose ($skipped_file);
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

?>
