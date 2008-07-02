<?php

	// Test conditions of address-taken aliasing.

	// The assumption is that $x = $y; does not create move $x or $y into an
	// alias-set if they are not already in one. However, $x =& $y adds $y and
	// $x to the same alias-set.

	$z = 6;
	$y = &$z; // y and z in same set.
	var_dump ($y);
	$x = $y; // x not in same set
	var_dump ($x, $y);
	$x = 5; // this assignment doesnt touch $y
	var_dump ($x, $y);

	// This means we can treat address-of as aliasing (even if its not strictly an address-of operator).

?>
