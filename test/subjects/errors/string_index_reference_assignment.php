<?php

	// TODO we should be able to detect this at compile-time

	// The type of Y doesnt matter here
	$x = "x";
	$y = "y";
	$x[0] =& $y;

?>
