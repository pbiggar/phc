<?php

	class X
	{
		function __toString ()
		{
			global $x;
			$x = 5;
			return "str";
		}
	}

	$x = new X;
	echo "First\n";
	echo ($x);
	echo "\n\nSecond\n";
	echo ($x);
	echo ("\n");

?>
