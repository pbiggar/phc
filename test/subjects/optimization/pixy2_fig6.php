<?php

	// Figure 6 from:
	// Precise alias analysis for static detection of web application vulnerabilities
	// By Nenad Jovanovic, Christopher Kruegel and Engin Kirda
	// PLAS 06

	a();

	function a()
	{
		$a1 =& $a2;
		b (&$a1, &$a2);
	}

	function b (&$bp1, &$bp2)
	{
	}

?>
