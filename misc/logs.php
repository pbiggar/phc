<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
	<head>
		<title>Error log</title>

	<body>
<?php

// print header

// get the relative path of the logs
$input_string = $_GET["q"];

// get absolute path
$string = "/tmp/phc_testing/trunk/test/logs/" . $input_string;

// get real absolute path
$real_path = realpath($string);

// check the file is within the sub-directory we want
if ($real_path 
		and strstr("/tmp/phc_testing/trunk/test/logs/", $real_path) == 0
		and is_file($real_path))
{
	// read the file
	$contents = file($real_path);

	// take a few special lines as headers
	$failure = array_shift($contents);
	print "<h1>$failure</h1>\n<hr />";

	// blank line
	array_shift($contents);

	while (preg_match("/^Command: /", $contents[0]))
	{
		$command = array_shift($contents);
		// strip console codes
		$command = preg_replace("/\[(\d;)?\d+m/", "", $command);
		print "<h4>$command</h4>\n";
	}

	$return_value = array_shift($contents);
	print "<h4>$return_value</h4>\n<hr/>\n";

	$output_line = array_shift($contents);
	print "<h4>$output_line</h4>\n";

	// print all the remaining lines
	foreach ($contents as $line)
	{
		chop($line);
		print "<p>$line</p>\n";
	}
}
else
{
	print "No such file: $input_string ($real_path)";
}

?>

	</body>
</html>
