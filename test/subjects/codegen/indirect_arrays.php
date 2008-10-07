<?php

	// References can be stored in arrays and objects (do objects separately).
	$i = 0;
	$y =& $i;
	$x[0] =& $y;
	$x["string"] =& $i;

	var_dump ($x);
	$x["string"] = 5; // set $x[0] too
	var_dump ($x);
?>
