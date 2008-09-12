<?php

	$y = 7;
	$a =& $y;
	$x[] = $a; // the reference isnt put in, the value is copied.
	$b =& $x[0];
	$b = 8;

	var_dump ($y, $a, $b, $x);


	$y1 = 7;
	$a1 =& $y1;
	$x1[] =& $a1; // the reference isnt put in, the value is copied.
	$b1 =& $x1[0];
	$b1 = 8;

	var_dump ($y1, $a1, $b1, $x1);

?>
