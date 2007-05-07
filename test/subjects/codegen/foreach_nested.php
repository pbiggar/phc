<?php

	$a = array ("a" => "A", "b" => "B", 0 => 7, "a" => "Z");
	$b = array ("w" => "W", "x" => "X", 5 => 12, "d" => "D");
	foreach ($a as $x)
	{
		var_export ($a);
		var_export ($x);
		foreach ($b as $y)
		{
			var_export ($b);
			var_export ($y);
		}
	}

	// with a break
	foreach ($a as $x)
	{
		var_export ($a);
		var_export ($x);
		foreach ($b as $y)
		{
			var_export ($b);
			break;
			var_export ($y);
		}
	}
?>
