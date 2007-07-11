<?php

	// Try accessing each data-type as if it were an array, then
	// assigning to it.
	$x = NULL;
	var_dump ($x[0]);
	var_dump ($x);

	$x0 = false;
	var_dump ($x0[0]);
	var_dump ($x0);

	$x1 = true;
	var_dump ($x1[0]);
	var_dump ($x1);

	$x2 = 7;
	var_dump ($x2[0]);
	var_dump ($x2);

	$x3 = 7.0;
	var_dump ($x3[0]);
	var_dump ($x3);

	// with a ref
	$x6 = NULL;
	$x7 =& $x6;
	$x7[5] = 6;
	var_dump ($x6);

	// TODO objects and resources

?>
