<?php

	// Figure 3 from:
	// Precise alias analysis for static detection of web application vulnerabilities
	// By Nenad Jovanovic, Christopher Kruegel and Engin Kirda
	// PLAS 06

	$x1 = 1;
	$x2 = 2;
	a (&$x1);
	echo $x1;
	echo $x2;

	function a (&$p)
	{
		$p =& $GLOBALS['x2'];
		$p = 5;
	}


?>
