#!/usr/bin/env php
<?php

set_include_path ("test/framework/external/" . PATH_SEPARATOR . "test/framework/" . get_include_path () );

require_once ("lib/header.php");
require_once ("Console/Getopt.php");

# Passing around code:
#   There is a problem that some code cannot be parsed (ie gotos and labels).
#   If we want to reduce code involving control-flow (and we do), then we need
#   to pass around XML, only unparsing it when necessary.


$num_steps = 0;

$N = count_statements ($xprogram);
$original = $N;
debug (1, "$N statements");

if ($N == 0)
  die ("No statements. Failing. Try -v -v for more info\n");

# confirm that we can find the bug automatically
if (!do_main_step ($xprogram, 0, 0, $filename))
	die ("Program does not appear to have a bug. Failing");


for ($k = (int)($N/2); $k >= 1; $k = (int)($k/2))
{
// RESTART:
	for ($i = 0; $i <= ($N-$k); $i += $k)
	{
	   $result = do_main_step ($xprogram, $i, $k, $filename);
		if ($result !== false)
		{
			$xprogram = $result;
			$N = count_statements ($xprogram);
			$k = $N; // the iteration will divide $N by 2
			debug (1, "Success, program reduced to $N statements");
			debug (1, ""); // put a blank line in the debug
			continue 2;
		}
		debug (1, ""); // put a blank line in the debug
	}
}

// we're done, it wont reduce any further
print "Finished. Reduced from $original to $N statements in $num_steps steps. Result in $filename.reduced\n";

$xprogram = add_comment ($xprogram);
$pprogram = convert ($xprogram, 0); // converted to PHP
$uprogram = convert ($xprogram, 1); // uppered
file_put_contents ("$filename.xreduced", $xprogram);
file_put_contents ("$filename.ureduced", $uprogram);
file_put_contents ("$filename.reduced", $pprogram);

function add_comment ($xprogram)
{
	global $opt_phc_prefix, $opt_pass;
	debug (2, "Adding comment");
	global $command_line;
	$out = run_safe ("$opt_phc_prefix/src/phc --read-xml=$opt_pass --run=$opt_phc_prefix/plugins/tools/add_comment.la --r-option=\"Reduced with command line '$command_line'\" --dump-xml=$opt_phc_prefix/plugins/tools/add_comment.la", $xprogram);
	return $out;
}

function reduce ($xprogram_string, $start, $num)
{
	global $opt_phc_prefix, $opt_pass;
	debug (2, "Reducing");
	$out = run_safe ("$opt_phc_prefix/src/phc --read-xml=$opt_pass --run=$opt_phc_prefix/plugins/tools/reduce_statements.la"
							 ." --r-option=$start:$num --dump-xml=$opt_phc_prefix/plugins/tools/reduce_statements.la",
							 $xprogram_string);
	return $out;
}

function convert ($xprogram_string, $upper)
{
	global $opt_phc_prefix, $opt_dont_upper, $opt_pass;

	if ($opt_dont_upper) $upper = false;
	debug (2, "Converting to PHP from XML" . ($upper ? " (uppered)" : ""));
	$upper = $upper ? " --convert-uppered" : ""; // TODO: if this is to be uppered, then we cant remove all?
	$out = run_safe ("$opt_phc_prefix/src/phc --read-xml=$opt_pass --dump$upper=$opt_pass --run=$opt_phc_prefix/plugins/tools/remove_all.la", $xprogram_string);
	return $out;
}

function count_statements ($xprogram_string)
{
	global $opt_phc_prefix;
	debug (2, "Counting statements");
	list ($out, $err, $exit) = run ("$opt_phc_prefix/src/phc --read-xml=$opt_phc_prefix/plugins/tutorials/count_statements_easy.la --run=$opt_phc_prefix/plugins/tutorials/count_statements_easy.la", $xprogram_string);
	if ($err || $exit !== 0)
	  die ("Error reading number of statements\n");
	debug (2, "Output is: $out");
	preg_match ("/(\d+) statements found/", $out, $matched) or die ();
	return $matched[1];
}

function run ($command, $stdin = NULL)
{

	debug (2, "Running command: $command");

	# complete_exec prints commands at opt_verbose = 1, but we want it at 2
	global $opt_verbose;
	$old = $opt_verbose;
	$opt_verbose = false;

	$result = complete_exec ($command, $stdin);
	$opt_verbose = $old;

	if ($result[0] == "Timeout")
		debug (2, "Command timed out");

	return $result;
}

/* Check outputs */
function run_safe ($command, $stdin = NULL)
{
	list ($out, $err, $exit) = run ($command, $stdin);

	if ($exit !== 0 || $err !== "")
		die ("Error ($exit): $err");

	return $out;
}

function above_debug_threshold ($level)
{
	global $opt_verbose;
	return ($level <= $opt_verbose);
}

function debug ($level, $message)
{
	if (above_debug_threshold ($level))
		print "$level: $message\n";
}

function dump ($filename, $output)
{
	debug (3, "Dumping to $filename");

	if (above_debug_threshold (3))
		file_put_contents($filename, $output);
}

# Reduce and test the program, passed as XML in $xprogram. Reduce it starting
# from the $start'th statement, by $num statements. For debugging, filename is
# the name of the script we're working on.
# Return false if the program couldnt reduce, or couldnt be tested, or the
# reduced program otherwise.
function do_main_step ($xprogram, $start, $num, $filename)
{
	// Within this step, we use src/phc, instead of $opt_phc_prefix, because we always want to test src/phc
	global $num_steps, $opt_interpret, $opt_failure, $opt_zero, $opt_main_command, $opt_pass;
	$num_steps++;

	# Reduce
	debug (1, "Attempting to reduce by $num statements, starting at statement $start");
	$xnew_program = reduce ($xprogram, $start, $num);
	$pnew_program = convert ($xnew_program, 0); // converted to PHP
	$unew_program = convert ($xnew_program, 1); // uppered
	$id = "{$num}_$start";
	dump ("$filename.xreduced_$id", $xnew_program);
	dump ("$filename.preduced_$id", $pnew_program);
	dump ("$filename.ureduced_$id", $unew_program);

	if ($xprogram == $xnew_program && $num != 0)
	{
		// this would happen if we dont remove any statements
		// if $num == 0, then this is intentional
		debug (1, "The two programs are identical. Skip.");
		return false;
	}

	debug (2, "Checking syntax errors");
	list ($php_out, $php_err, $php_exit) = run ("php -l", $unew_program);
	if ($php_exit || $php_err) // if the reduced case causes a PHP error, ignore.
	{
		debug (1, "Error running through PHP. Skip. (exit_code: $php_exit, error: $php_err)");
		return false;
	}

	# do this all here to avoid littering the function with it
	if ($opt_failure)
	{
		debug (2, "Getting output when run with failure plugin");
		list ($phc_out, $phc_err, $phc_exit) = run ("src/phc --read-xml=$opt_pass --run=$opt_failure", $xnew_program);
		if (preg_match ("/Failure$/", $phc_out))
		{
			debug (2, "Success, bug kept in");
			dump ("$filename.phc_out_$id", $phc_out);
			dump ("$filename.xsuccess_$id", $xnew_program);
			dump ("$filename.psuccess_$id", $pnew_program);
			dump ("$filename.usuccess_$id", $unew_program);
			return $xnew_program;
		}
		else
			return false;
	}

	# Run through PHP
	debug (2, "Getting PHP output");
	list ($php_out, $php_err, $php_exit) = run (get_php_command_line ($filename, true), $unew_program);
	$php_out = homogenize_all ($php_out, $filename);
	dump ("$filename.php_out_$id", $php_out);
	if ($opt_zero && $php_exit)
	{
		debug (1, "Error running through PHP. Skip. (exit_code: $php_exit, error: $php_err)");
		return false;
	}


	$phc_error = false;
	if ($opt_interpret)
	{
		# Run it through PHP til the specified pass, then run the output through PHP
		debug (2, "Getting PHP output after running through phc");

		global $opt_upper;
		$upper = $opt_upper ? "u" : "";
		list ($phc_out, $phc_err, $phc_exit) = run ("src/phc --read-xml=$opt_pass --{$upper}dump=$opt_interpret $opt_main_command", $xnew_program);
		if ($phc_err === "" && $phc_exit === 0)
		{
			list ($my_out, $my_err, $my_exit) = run (get_php_command_line ($filename, true), $phc_out);
			$my_out = homogenize_all ($my_out, $filename);
			dump ("$filename.phci_out_$id", $my_out);
		}
		else $phc_error = true;
	}
	else
	{
		# Compile and run
		debug (2, "Getting compiled phc output");
		list ($phc_out, $phc_err, $phc_exit) = run ("src/phc --read-xml=$opt_pass -c $opt_main_command", $xnew_program);
		if ($phc_err === "" && $phc_out === "" && $phc_exit === 0)
		{
			list ($my_out, $my_err, $my_exit) = run ("./a.out");
			$my_out = homogenize_all ($my_out, $filename);
			dump ("$filename.phc_out_$id", $my_out);
		}
		else $phc_error = true;
	}

	if (!$phc_error)
	{
		if ($php_out === "Timeout" || $my_out === "Timeout")
		{
			debug (1, "phc error. Skip.");
			return false;
		}

		if ($php_err === "Timeout") # if my_err is timeout, we've kept the bug in
		{
			debug (1, "Timeouts. Skip.");
			return false;
		}
	}

	if (  $phc_error
		|| $php_err !== $my_err
		|| $php_exit !== $my_exit
		|| $php_out !== $my_out) // success, we've reduced it while keeping the bug in
	{
		debug (2, "Success, bug kept in");
		dump ("$filename.xsuccess_$id", $xnew_program);
		dump ("$filename.psuccess_$id", $pnew_program);
		dump ("$filename.usuccess_$id", $unew_program);
		return $xnew_program;
	}

	debug (2, "Bug removed. Skip.");
	return false;
}
?>
