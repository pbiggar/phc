#!/usr/bin/env php
<?php

$php = "php";

set_include_path ("test/framework/external/" . PATH_SEPARATOR . "test/framework/" . get_include_path () );

require_once ("lib/header.php");
require_once ("Console/Getopt.php");

require_once ("Reduce.php");


$cg = new Console_Getopt();
$command_line = join (" ", $cg->readPHPArgv());
$opt_result = $cg->getopt($cg->readPHPArgv(), "vhc:rdDf:i:UuF:ZP:m:p:");
if (!is_array ($opt_result))
	die ($opt_result->message."\n");

list ($opts, $arguments) = $opt_result;
$opt_verbose = 0;
$opt_help = false;
$opt_command = "";
$opt_main_command = "";
$opt_pass = "AST-to-HIR";
$opt_xml = NULL;
$opt_interpret = false;
$opt_dont_upper = false;
$opt_upper = false;
$opt_failure = false;
$opt_zero = true;
$opt_phc_prefix = ".";
foreach ($opts as $opt) 
{
	switch ($opt[0])
	{
		case 'h': $opt_help = true; break;
		case 'v': $opt_verbose += 1; break;
		case 'U': $opt_dont_upper = true; break;
		case 'u': $opt_upper = true; break;
		case 'c': $opt_command .= $opt[1]; break;
		case 'm': $opt_main_command .= $opt[1]; break;
		case 'x': $opt_xml = $opt[1]; break;
		case 'i': $opt_interpret = $opt[1]; break;
		case 'F': $opt_failure = $opt[1]; break;
		case 'Z': $opt_zero = true; break;
		case 'P': $opt_phc_prefix = $opt[1]; break;
		case 'p': $opt_pass = $opt[1]; break;
	}
}
foreach ($opts as $opt)  // these need to wait until opt_phc_prefix is set
{
	switch ($opt[0])
	{
		case 'r': $opt_command .= "--run=$opt_phc_prefix/plugins/tools/debug_zval.la --dump-xml=$opt_phc_prefix/plugins/tools/debug_zval.la"; break;
		case 'd': $opt_command .= "--run=$opt_phc_prefix/plugins/tools/demi_eval.la --r-option=true --dump-xml=$opt_phc_prefix/plugins/tools/demi_eval.la"; break;
		case 'D': $opt_command .= "--run=$opt_phc_prefix/plugins/tools/demi_eval.la --r-option=false --dump-xml=$opt_phc_prefix/plugins/tools/demi_eval.la"; break;
	}
}

if ($opt_help || count ($arguments) == 0)
{
	die (<<<EOL
reduce - A program to automatically reduce test cases for phc - phpcompiler.org

Usage: reduce [OPTIONS] filename

Options:
    -h     Print this help message
    -v     Verbose. Can be set more than once. Set once, prints actions; set 
           twice, prints commands executed; set thrice, dumps results of 
           intermediate stages.
    -p     Mnemoic: pass. Perform the reduction at the specified pass.
    -P     Since src/phc is broken, another version can be specified to do the
           conversion steps, with this prefix.
    -c     Pass as arguments to the first phc. Be sure to include an --dump-xml
           command, or nothing will happen.
    -m     Pass as arguments to the main phc. Default ""
    -r     Mnemonic: refcount. The equivalent of "-c--run
           plugins/tools/debug_zval.la -dump-xml=plugins/tools/debug_zval.la".
    -d     The equivalent of "-c--run=plugins/tools/demi_eval.la
           -dump-xml=plugins/tools/demi_eval.la --r-option=true".
    -D     The equivalent of "-c--run=plugins/tools/demi_eval.la
           -dump-xml=plugins/tools/demi_eval.la --r-option=false".
    -x     Use the passed XML file as the the first program, instead of calling
           phc.
    -i     Mnemonic: Interpret. Instead of compiling the script, dump it at the
           specified pass and interpret it.
    -U     Don't print 'upper' debug files (not related to -u)
    -u     Used with -i, 'upper's before dumping (not related to -U)
    -F     Mnemonic: Failure. Used for plugins which print "Failure" to
           indicate error. Run phc with the plugin to determine failure.
    -Z     Require script to return zero when run through interpreter

Sample commands:
    reduce -v test/subjects/codegen/0001.php
    reduce "-c--run=plugins/tools/debug_zval.la -dump-xml=plugins/tools/debug_zval.la" test/subjects/codegen/0001.php
    reduce -v 0001.uhir.php
    reduce -F plugins/tests/limit_assignments.la test/subjects/codegen/bench_simple.php

EOL
	);
}


$filename = $arguments[0];
$reduce = new Reduce ($filename);

$reduce->set_phc ("src/phc");
$reduce->set_comment ($command_line);
$reduce->set_plugin_path ($opt_phc_prefix);
$reduce->set_run_command_function ("myrun");
$reduce->set_debug_function ("mydebug");
$reduce->set_dump_function ("mydump");

// Checking functions
$reduce->set_checking_function ("check_against_compiled");

if ($opt_failure)
	$reduce->set_checking_function ("check_for_failure_string");

if ($opt_interpret)
	$reduce->set_checking_function ("check_against_interpreted");


$input = file_get_contents ($filename);

// TODO: call this on the first instance
if ($opt_command != "")
{
	// TODO use opt_command on the first instance
	// TODO: use --no-xml-attrs
	throw new Exception ("TODO");
}

if ($opt_xml)
{
	$result = $reduce->run_on_xml ($input);
}
else
{
	$result = $reduce->run_on_php ($input);
}

print "Writing reduced file to $filename.reduced\n";
file_put_contents ("$filename.reduced", $result);



/*
 * Callbacks for reduce
 */
function myrun ($command, $stdin = NULL)
{
	if ($stdin === NULL)
		mydebug (2, "Running command: $command");
	else
		mydebug (2, "Running command with stdin: $command");

	# complete_exec prints commands at opt_verbose = 1, but we want it at 2
	global $opt_verbose;
	$old = $opt_verbose;
	$opt_verbose = false;

	$result = complete_exec ($command, $stdin);
	$opt_verbose = $old;

	if ($result[0] == "Timeout")
		mydebug (2, "Command timed out");

	return $result;
}

function above_debug_threshold ($level)
{
	global $opt_verbose;
	return ($level <= $opt_verbose);
}

function mydebug ($level, $message)
{
	if (above_debug_threshold ($level))
	{
		print "$level: $message\n";
	}
}

function mydump ($suffix, $output)
{
	global $filename;
	if (above_debug_threshold (3))
	{
		mydebug (3, "Dumping to $filename.suffix");
		file_put_contents ("$filename.$suffix", $output);
	}
}

function failure_check ($program)
{
	throw new Exception ("TODO- what does this do?");
	global $opt_pass, $opt_failure;


	mydebug (2, "Getting output when run with failure plugin");
	list ($out, $err, $exit) = run ("src/phc --read-xml=$opt_pass --run=$opt_failure", $program);
	if (preg_match ("/Failure$/", $out))
	{
		mydebug (2, "Success, bug kept in");
		return true;
	}
	else
		return false;
}



function check_against_interpreted ($program)
{
	global $filename;
	// Interpret
	$result = run_with_php ($program, $filename);

	if ($result == false)
		return false;

	list ($php_out, $php_err, $php_exit) = $result;


	$result = interpret_with_phc ($program, $filename);
	list ($phc_out, $phc_err, $phc_exit) = $result;

	if (	$phc_out != $php_out
		|| $phc_err != $php_err
		|| $phc_exit != $php_exit)
	{
		mydebug (1, "Outputs differ");
		return true;
	}

	mydebug (1, "Outputs are the same");
	return false;
}

function interpret_with_phc ($program)
{
	global $opt_pass, $opt_main_command, $opt_interpret, $filename;

	// TODO: support uppering

	# Compile and run
	mydebug (2, "Getting compiled phc output");

	$command = "src/phc --dump=$opt_interpret $opt_main_command";
	list ($out, $err, $exit) = myrun ($command, $program);

	if ($err !== "" || $exit !== 0)
	{
		mydebug (1, "Error interpreting ($exit), skip: $err");
		return false;
	}

	list ($out, $err, $exit) = myrun (get_php_command_line ($filename, true), $out);
	$out = homogenize_all ($out, $filename);

	return array ($out, $err, $exit);
}

function run_with_php ($program)
{
	global $opt_zero, $filename;

	# Run through PHP
	mydebug (2, "Getting PHP output");

	$command = get_php_command_line ($filename, true);
	list ($out, $err, $exit) = myrun ($command, $program);

	$out = homogenize_all ($out, $filename);

	if ($opt_zero && $exit)
	{
		mydebug (1, "Exit code not zero, skip. (out: $out, exit code: $exit, error: $err)");
		return false;
	}

	if ($out == "Timeout")
	{
		mydebug (1, "Timed out");
		return false;
	}

	return array ($out, $err, $exit);
}

function run_with_phc ($program, $filename)
{
	global $opt_pass, $opt_main_command;

	# Compile and run
	mydebug (2, "Getting compiled phc output");

	$command = "src/phc --read-xml=$opt_pass -e $opt_main_command";
	list ($out, $err, $exit) = myrun ($command, $program);

	if ($out == "Timeout")
	{
		mydebug (1, "Timed out");
		return false;
	}

	$out = homogenize_all ($out, $filename);

	return array ($out, $err, $exit);
}

function check_against_compiled ($program)
{
	global $filename;
	// Interpret
	$result = run_with_php ($program, $filename);

	if ($result == false)
		return false;

	list ($php_out, $php_err, $php_exit) = $result;

	// Compile
	$result = run_with_phc ($program, $filename);

	if ($result == false)
		return false;

	list ($phc_out, $phc_err, $phc_exit) = $result;

	if ($phc_out != $php_out
			|| $phc_err != $php_err
			|| $phc_exit != $php_exit)
	{
		mydebug (1, "Outputs differ");
		return true;
	}

	mydebug (1, "Outputs are the same");
	return false;
}
