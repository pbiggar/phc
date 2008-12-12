<?php

	// Test code generation for rvalues doesnt abort.
	// { phc-option: --disable=ashred --generate-c }

	$x[1] = 2;
	$y = $x[3];

	$$x = 4;

	unset ($x[5]);

	isset ($x[6]);

	$a = 7 + $b;
	$c = $b + 8;

	var_dump (9);

	var_dump ($x, $y, $a, $c);

	function x ()
	{
		return 5;
	}

?>
