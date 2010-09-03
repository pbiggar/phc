<?php

	// Check that SCCP doesnt overwrite $y =& $x;

	$x = 5;
	$y =& $x;
	$y = 4;
	var_dump ($y);
	var_dump ($x);

?>
