<?php

	// When shredding, we need to keep from accidentally inserting into the
	// array, which can happen if we introduce superfluous &s. Comments indicate
	// safe shreddings for the statements

	$x0[0]; // $t = $x0[0]
	var_dump ($x0);

	$t0 = $x1[0][0]; // $t0 = $x1[0]; $t2 = $t0[0];
	var_dump ($x1);

	$t0 =& $x1[0][0]; // $t0 =& $x1[0]; $t2 =& $t0[0];
	var_dump ($x1);

	$x2[0] = 7;
	var_dump ($x2); // $x2[7]; (and not $t =& $x2[0]; $t = 7)


	// Read by reference, overwrite, then check the read
	$t1 =& $x[0];
	$t2 =& $t1;
	$x0 = 7;
	var_dump ($t2);

?>
