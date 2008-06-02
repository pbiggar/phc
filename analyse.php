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
		"src/phc --sdump=clar $filename > $base.clp",
		"3rdparty/clpa/bin/clpa --debug parse_warnings $base.clp",
		"rm $base.clp",

		// Turn into CFG
#		"3rdparty/clpa/bin/clpa --debug eval_rule src/analyse/do_cfg.clp",
		"3rdparty/clpa/bin/clpa src/analyse/do_cfg.clp",

		// create CFG graphs
		"dot -Tps CFG.dot > CFG.ps",
		"rm -f CFG.dot",
#		"dot -Tps PPs.dot > PPs.ps",
		"rm -f PPs.dot",


		# Run Dead-code elimination
#		"3rdparty/clpa/bin/clpa --debug eval_rule src/analyse/dce.clp",
		"3rdparty/clpa/bin/clpa src/analyse/dce.clp",


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
