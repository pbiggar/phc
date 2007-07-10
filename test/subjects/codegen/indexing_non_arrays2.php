<?php

	// Try accessing each data-type as if it were an array, then
	// assigning to it.
	$x = NULL;
	$x[5] = false;
	var_dump ($x[0]);
	var_dump ($x[5]);
	var_dump ($x);


	$x0 = false;
	$x0[5] = false;
	var_dump ($x0[0]);
	var_dump ($x0[5]);
	var_dump ($x0);


	$x1 = true;
	$x1[5] = false;
	var_dump ($x1[0]);
	var_dump ($x1[5]);
	var_dump ($x1);


	$x2 = 7;
	$x2[5] = false;
	var_dump ($x2[0]);
	var_dump ($x2[5]);
	var_dump ($x2);


	$x3 = 7.0;
	$x3[5] = false;
	var_dump ($x3[0]);
	var_dump ($x3[5]);
	var_dump ($x3);

	// TODO reenable

//	$x4 = "string";
//	var_dump ($x4[0]);
//	var_dump ($x4);

//	$x5 = "string";
//	var_dump ($x5[17]); // index outside the string
//	var_dump ($x5);

	// TODO objects and resources

?>
