<?php

	// Figure 8 from:
	// Precise alias analysis for static detection of web application vulnerabilities
	// By Nenad Jovanovic, Christopher Kruegel and Engin Kirda
	// PLAS 06

	a();

	function a()
	{
		$a1 =& $GLOBALS['x1'];
		b (&$a1);
	}

	function b (&$bp1)
	{
	}


?>
