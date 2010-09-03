<?php

	// Figure 5 from:
	// Precise alias analysis for static detection of web application vulnerabilities
	// By Nenad Jovanovic, Christopher Kruegel and Engin Kirda
	// PLAS 06

	a();

	function a ()
	{
		$a1 =& $a2;
		$GLOBALS['x1'] = $GLOBALS['x2'];
		b ();
	}

	function b ()
	{
		$GLOBALS['x3'] =& $GLOBALS['x1'];
	}

?>
