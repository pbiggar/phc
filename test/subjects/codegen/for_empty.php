<?php

	// for loops dont work properly
	for (;;)
	{
		$x ++;
		var_dump ($x);
		// we need to exit
		if ($x > 10)
			exit (0);
	}
?>
