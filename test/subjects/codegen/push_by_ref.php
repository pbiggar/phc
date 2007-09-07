<?php

	$x = 7;
	$a = array ();
	$a[] =& $x;
	var_dump ($x);
	var_dump ($a);

	$a[0] = 2;
	var_dump ($x);
	var_dump ($a);
?>
