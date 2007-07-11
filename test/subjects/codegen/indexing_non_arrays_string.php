<?php

	// Try accessing each data-type as if it were an array, then
	// assigning to it.

	$x4 = "string";
	var_dump ($x4[0]);
	var_dump ($x4);

	$x5 = "string";
	var_dump ($x5[17]); // index outside the string
	var_dump ($x5);

?>
