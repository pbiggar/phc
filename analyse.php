#!/usr/bin/env php
<?php

	if ($argc != 2)
		die ("usage: ./analyse.php FILENAME\n");

	$filename = $argv[1];
	$base = basename ($filename, ".php");

	// create .db files in the current directory
	`src/phc --sdump=ast $filename > $base.clp`;

	// run clpa with a sample analysis on it
	print `3rdparty/clpa/bin/clpa $base.clp 2>&1`;


?>
