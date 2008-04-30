<?php

	// have function called before the default.
	function f ()
	{
		echo "f called\n";
		return 8;
	}

	$x = 7;
	switch ($x)
	{
		case 6:
			echo "6\n";
		default:
			echo "default\n";
		case f():
			echo "f\n";
	}

?>
