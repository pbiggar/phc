<?php

	// Try accessing each data-type as if it were an array
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

	$x4 = "string";
	var_dump ($x4[0]);
	var_dump ($x4);

	$x5 = "string";
	var_dump ($x5[17]); // index outside the string
	var_dump ($x5);

	// TODO objects and resources

?>
