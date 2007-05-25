<?php

	$a = array ("a" => "A", "b" => "B", 0 => 7, "a" => "Z");
	foreach ($a as $x)
	{
		var_export ($x);
		foreach ($a as $y)
		{
			var_export ($y);
		}
		echo "\n";
	}
	echo "----------------------------------\n";
	var_export ($x);
	var_export ($y);


	// outer with reference, inner without
	foreach ($a as &$x)
	{
		var_export ($x);
		foreach ($a as $y)
		{
			var_export ($y);
		}
		echo "\n";
	}
	echo "----------------------------------\n";
	var_export ($x);
	var_export ($y);

	// inner with reference, outer without
	// implicit unset $x here
	foreach ($a as $x)
	{
		var_export ($x);
		foreach ($a as &$y)
		{
			var_export ($y);
		}
		echo "\n";
	}
	echo "----------------------------------\n";
	var_export ($x);
	var_export ($y);

	// with references
	foreach ($a as &$x)
	{
		var_export ($x);
		foreach ($a as &$y)
		{
			var_export ($y);
		}
		echo "\n";
	}
	echo "----------------------------------\n";
	var_export ($x);
	var_export ($y);

	// try altering the array
	$a = array ("a" => "A", "b" => "B", 0 => 7, "a" => "Z");
	foreach ($a as &$x)
	{
		var_export ($x);
		$x *= 2;
		foreach ($a as &$y)
		{
			$y *= 3;
			var_export ($y);
		}
	}
	var_export ($x);
	var_export ($y);


?>
