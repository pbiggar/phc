<?php

	// try to get a sneaky reference to a constant
	$y = 5;
	$x =& $y;

	// This copies the value, so the const isnt damaged.
	define (ACONST, $x);

	var_dump ($x);

	$y = 6;

	var_dump ($x);
	var_dump (ACONST);

?>
