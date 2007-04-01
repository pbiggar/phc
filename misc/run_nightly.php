#!/usr/bin/php -Cq
<?php

ini_set("memory_limit","32M");

function calc_time()
{
	return date("H:i:s");
}

function strip_console_codes ($string)
{
	// strip console codes
	$string = preg_replace("/\[1;\d\dm/", "", $string);
	$string = preg_replace("/\[0m/", "", $string); 
	return $string;
}



function get_header ($title, $command)
{
	global $spacer;
	$time = calc_time();
	$header = "$spacer($time)		$title:\n$spacer";
	$header .= "$command\n";
	return $header;
}

function run_command ($title, $command, $directory = false)
{
	global $output;
	$header = get_header ($title, $command);
	$command = "$command 2>&1"; // hardcode to be safe
	if ($directory)
	{
		chdir ($directory) or die ("Error changing directory ($directory)");
	}
	exec ($command, $result, $ret_value);
	$result = join ("\n", $result);
	$result = strip_console_codes ($result);
	if ($ret_value)
	{
		$output = "Error running command: $command (return $ret_value)\n\nOutput:\n$result\n\nPrevious output:\n$output";

		// mail the output
		mail("phc-internals@phpcompiler.org", "Nightly testing", $output);
		exit();
	}

	return "$header$result\n\n";
}


	$root = "/tmp/phc_testing";
	$spacer = "-------------------------------------------------\n";
	$output = "";

	$output .= run_command ("Removing old version", "rm -Rf /tmp/phc_testing");
	mkdir($root) or die ("Mkdir in /tmp/ failing is very unlikely. PANIC");

	$output .= run_command ("Checking out source", "svn export -q http://phc.googlecode.com/svn/trunk", $root);
	$output .= run_command ("Checking out website", "svn export -q http://phc.googlecode.com/svn/www", $root);
	$output .= run_command ("Touch generated", "touch src/generated/*", "$root/trunk");
	$output .= run_command ("Configure", "./configure --prefix=$root/installed", "$root/trunk");
	$output .= run_command ("Make", "make", "$root/trunk");

	// We use this in the summary later
	$test_summary = run_command ("Run tests", "php test/framework/driver.php -l -p", "$root/trunk");
	$output .= $test_summary;

	$output .= run_command ("Run installer", "make install", "$root/trunk");
	$output .= run_command ("Test installed components", "php test/framework/driver.php -l -p -i", "$root/trunk");

	$found = run_command ("Errors", "find test/logs 2>&1 | grep '.php.log$'", "$root/trunk");
	// get ready for hosting
	$found = preg_replace("/^test\/logs\//m", "http://godiva.cs.tcd.ie/~pbiggar/logs.php?q=", chop($found));
	$output .= $found;

	// dont use the doxy output, it's worthless
	$doxy_header = get_header ("Generating docs", "doxygen misc/Doxyfile");
	run_command ("Generating docs", "doxygen misc/Doxyfile", "$root/trunk");
	$doxy_header .= "Generated docs at http://godiva.cs.tcd.ie/~pbiggar/doxy\n";
	$output .= $doxy_header;
	if (file_exists ("$root/trunk/doxy_warnings"))
	{
		$doxy_warnings = join("\n", file("$root/trunk/doxy_warnings")); // read the warnings
		$output .= $doxy_warnings;
	}
	else $output .= "No doxy_warnings file found";
	$output .= "\n\n";


	// we're now finished the tests
	$time = calc_time();
	$output .= "$spacer($time)		Done.\n$spacer";


	// tack a summary onto the front of it
	$test_summary = preg_replace("/.*rm -Rf test\/logs\/\*\n/s", "", $test_summary);
	$summary = "$spacer		Summary:\n$spacer";
	$summary .= $test_summary;

	if (strlen ($output) > 200000)
	{
		$output = "Output too long, trimmed to last 200K:\n\n"
			. substr ($output, -200000);
	}

	$output = $summary . $output;

	$output = strip_console_codes ($output);

	// mail the output
	mail("phc-internals@phpcompiler.org", "Nightly testing", $output);

?>
