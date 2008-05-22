#!/usr/bin/env php
<?php

	require_once ("test/framework/lib/header.php");

	if ($argc != 2)
		die ("usage: ./analyse.php FILENAME\n");

	$filename = $argv[1];
	$base = basename ($filename, ".php");

	$commands = array (
		// create .db files in the current directory
		"rm -f *.db",
		"src/phc --sdump=mir $filename > $base.clp",
		"3rdparty/clpa/bin/clpa --debug parse_warnings $base.clp",
		"rm $base.clp",

		// run clpa with a sample analysis on it
		"3rdparty/clpa/bin/clpa --debug add_rule src/analyse/cfgdot.clp",

		// create graph
		"dot -Tps Test.dot > Test.ps"
	);

	foreach ($commands as $command)
	{
		print "Command: $command\n";
		list ($out, $err, $exit) = complete_exec ($command);
		if ($out or $err or $exit)
			print "out: '$out', err: '$err', exit: '$exit'\n";
		if ($exit !== 0)
			die ("Bad exit code\n");
	}


?>
