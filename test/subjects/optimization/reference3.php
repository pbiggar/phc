<?php

	// The references node may exist
	if ($argc == 2)
		$x[4] = 4;


	$y =& $x[4];


	var_dump ($y);

	$y = 5;

	var_dump ($x);

?>
