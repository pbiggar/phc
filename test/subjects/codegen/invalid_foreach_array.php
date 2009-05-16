<?php

	include ("test/subjects/parsing/scalar_array.php");

	$x = new stdclass;
	$x->f = 5;
	$short_scalar_array[] = $x;

	foreach ($short_scalar_array as $scalar)
	{
		var_dump ($scalar);
		foreach ($scalar as $y => $z)
		{
			echo "$y => $z\n";
		}
	}

?>
