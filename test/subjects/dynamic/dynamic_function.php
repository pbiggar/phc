<?php

	$x = 17;
	if ($x * $x > 345)
	{
		function f($a, $b, $c)
		{
			echo "Function 1 with $a, $b and $c\n";
		}
	}
	else
	{
		function f($a, $b, $c)
		{
			echo "Function 2 with $a, $b and $c\n";
		}

		function g($a, $b)
		{
			echo "Function g with $a and $b\n";
		}
	}

	f (1, 2, 3);
	if (function_exists("g"))
	{
		g (7,8);
	}
?>

