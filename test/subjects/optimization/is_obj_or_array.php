<?php

	class X {}

	$x = array (1, 2, 3);
	$y = new X;
	$z = 5;

	var_dump (is_array ($x));
	var_dump (is_array ($y));
	var_dump (is_array ($z));

	var_dump (is_object ($x));
	var_dump (is_object ($y));
	var_dump (is_object ($z));

?>
