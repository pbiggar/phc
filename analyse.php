#!/usr/bin/env php
<?php

	require_once ("test/framework/lib/header.php");
	require_once ("test/framework/external/Console/Getopt.php");


	$cg = new Console_Getopt();
	$getopt = $cg->getOpt($cg->readPHPArgv(), "v", array ("verbose"));
	if ($getopt instanceof PEAR_Error)
		die ("Command line error: {$getopt->message}\n");

	list ($opts, $arguments) = $getopt;
	foreach ($opts as $opt) 
	{
		if ($opt[1] == NULL) $options{$opt[0]} = "";
		else $options{$opt[0]} = ($opt[1]);
	}
	$opt_verbose = isset($options{"v"});



	if (count ($arguments) != 1)
		die ("usage: ./analyse.php FILENAME\n");

	$filename = $arguments[0];
	$base = basename ($filename, ".php");

	$clpa = "3rdparty/clpa/bin/clpa";
	if ($opt_verbose) $clpa .= " --debug add_rule";

	$commands = array (
		// create .db files in the current directory
		"rm -f *.db",
		"src/phc --sdump=clar $filename > $base.clp",
		"$clpa --debug parse_warnings $base.clp",
		"rm $base.clp",

		// Turn into CFG
		"$clpa src/analyse/do_cfg.clp",

		# Run Dead-code elimination
		"$clpa src/analyse/dce.clp",

		// create CFG graphs
		"rm -f *.ps",
		"for i in *.dot; do dot -Tps \$i > \$i.ps; done",
		"rm -f *.dot",

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
