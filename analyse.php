#!/usr/bin/env php
<?php

	require_once ("test/framework/lib/header.php");

	if ($argc != 2)
		die ("usage: ./analyse.php FILENAME\n");

	$filename = $argv[1];
	$base = basename ($filename, ".php");

	// create .db files in the current directory
	$opt_verbose = true;
	var_dump (complete_exec ("rm *.db"));
	var_dump (complete_exec ("src/phc --sdump=ast $filename > $base.clp"));
	var_dump (complete_exec ("3rdparty/clpa/bin/clpa --debug parse_warnings $base.clp"));
#	var_dump (complete_exec ("rm $base.clp"));

	// run clpa with a sample analysis on it
	var_dump (complete_exec ("3rdparty/clpa/bin/clpa src/analyse/cfgdot.clp"));


?>
