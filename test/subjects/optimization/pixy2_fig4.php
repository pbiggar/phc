<?php

	// Figure 4 from:
	// Precise alias analysis for static detection of web application vulnerabilities
	// By Nenad Jovanovic, Christopher Kruegel and Engin Kirda
	// PLAS 06


	$a =& $b;
	if (rand())
	{
		$c =& $d;
		$e =& $d;
	}
?>
