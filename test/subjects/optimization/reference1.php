<?php

	// More than 1 value for an index on the rhs 

	if ($argc == 1)
		$x = "str";
	else
		$x = "another_strin";

	$y =& $a[$x];

	$y = 0;
	var_dump ($a);

?>
