<?php

	// try it without arry_pop
	$a = array (1, 2, 3, 4);
	$b = $a[$argc];
	$a[$argc] = NULL;

	// same thing
	$x = array (1, 2, 3, 4);
	$y = array_pop ($x);

	var_dump ($a, $b, $x, $y);

?>
