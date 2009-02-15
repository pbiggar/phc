<?php

	// reduced by hand from PHPWhirl. self refers (statically) to the class its in.

	class A
	{
		static $B = 5;

		function x ()
		{
			echo self::$B;
		}
	}

	$x = new A;
	$x->x();

?>
