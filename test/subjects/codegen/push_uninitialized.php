<?php

	require ("parsing/scalar_array.php");

	$x[] = 5;
	var_dump ($x);

	foreach ($scalar_array as $scalar)
	{
		// skip string, and do them last
		if (is_string ($scalar) && strlen ($scalar) > 0)
			continue;

		echo "\nTrying: ";
		var_dump ($scalar);

		$x = $scalar;
		$x[] = 5;
		var_dump ($x);

//		$x = $scalar;
//		$y =& $x[];
//		$y = 6;
//		var_dump ($x);
	}

	$x = "str";
	$x[] = 5;
	var_dump ($x);

?>
