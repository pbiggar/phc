<?php

	// Figure 2 from:
	// Precise alias analysis for static detection of web application vulnerabilities
	// By Nenad Jovanovic, Christopher Kruegel and Engin Kirda
	// PLAS 06

	$evil = "evil";

	$b = "nice";
	$a =& $b;
	$a = $evil;
	echo $b;


?>
