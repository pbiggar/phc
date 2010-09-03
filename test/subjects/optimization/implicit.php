<?php

	// test implicit conversions to arrays
	for ($i = 0; $i < $argc; $i++)
	{
		$x[$i] = 5;
		var_dump ($x);
		$y = $x;
		$x = NULL;
	}

?>
