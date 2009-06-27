<?php

	include ("parsing/scalar_array.php");

	class X {}
	class Y
	{
		function __toString ()
		{
			return "some string";
		}
	}

	$scalar_array[] = new X;
	$scalar_array[] = new Y;

	foreach ($scalar_array as $x)
	{
		var_dump ($x);
		$x++;
		var_dump ($x);
		$x--;
		var_dump ($x);
	}
