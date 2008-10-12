<?php

	// References can be stored in arrays and objects (do objects separately).
	$i = 0;
	$y =& $i;
	$x->f =& $y;
	$x->g =& $i;

	var_dump ($x);
	$x->g = 5; // set $x->f too
	var_dump ($x);
?>
