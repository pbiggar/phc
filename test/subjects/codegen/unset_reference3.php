<?php

	$x = 7;
	$y = &$x;
	$z = &$y;

	// unset remove $y from the COW set, but it doesnt affect the value of $x or $z	
	var_dump ($y);
	unset ($y);
	var_dump ($y);

	var_dump ($z);
	$z = 5;
	var_dump ($x);
?>
