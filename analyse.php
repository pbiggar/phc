#!/usr/bin/env php
<?php

	$filename = $argv[0];

	// create .db files in the current directory
	print `src/phc --xdump=mir $filename 2>&1 | 3rdparty/clpa/bin/phccc 2>&1`;

	// run clpa with a sample analysis on it
	print `3rdparty/clpa/bin/clpa analyses/sample_analysis.clp`;


?>
