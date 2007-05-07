<?php

	$array = array (1 => "a", 2 => "b", 3 => "c", 4 => "d");

	// standard foreach, no references
	$temp_array = $array;
	while (list ($key, $val) = each ($temp_array))
	{
		var_export ($key);
		var_export ($val);
	}
	var_export ($array);
	reset ($array);
	echo "----------------------------------\n";

	// standard foreach, with references
	$temp_array = &$array;
	while (list ($key, ) = each (&$temp_array))
	{
		$val = $temp_array [$key];
		var_export ($key);
		var_export ($val);
	}
	var_export ($array);
	reset ($array);
	echo "----------------------------------\n";

	// refernce done by in-loop copy, single param to list
	while (list ($key) = each (&$temp_array))
	{
		$val = &$key;
		var_export ($key);
		var_export ($val);
	}
	var_export ($array);
	reset ($array);
	echo "----------------------------------\n";

	// refernce done by in-loop copy, two params to list
	while (list ($key, ) = each (&$temp_array))
	{
		$val = &$key;
		var_export ($key);
		var_export ($val);
	}
	var_export ($array);
	reset ($array);
	echo "----------------------------------\n";

	// refernce done by in-loop copy, no list
	while ($key = each (&$temp_array))
	{
		$val = &$key;
		var_export ($key);
		var_export ($val);
	}
	var_export ($array);
	reset ($array);
	echo "----------------------------------\n";


	// now a foreach
	foreach ($array as $key => &$val)
	{
		$key *= 2;
		var_export ($key);
		var_export ($val);
	}
	var_export ($array);
	reset ($array);
	echo "----------------------------------\n";


		// with references
	// From the php documentation:
	//	  Because assigning an array to another variable resets the original
	//	  arrays pointer, our example above would cause an endless loop had we
	//	  assigned $fruit to another variable inside the loop.
	// I can't seem to replicate this
	reset ($a);
	while (list ($x, ) = each (&$a))
	{
		$b = $a;
		$c =& $a;
		var_export ($a[$x]);
	}
	echo "\n";
	echo "----------------------------------\n";


	foreach ($a as &$x)
	{
		$b = $a;
		$b[3] = "A"; // php is copy on write
		var_dump ($b[0]);
		var_dump ($a);
		var_dump ($b);
	}
	echo "----------------------------------\n";

	foreach ($a as $x)
	{
		$b = $a;
		$b[3] = "A"; // php is copy on write
		var_dump ($b[0]);
		var_dump ($a);
		var_dump ($b);
	}
	echo "----------------------------------\n";


	foreach ($a as &$x)
	{
		// move $a's iterator to the end
		while (each ($a)) {}
		$b = $a;
		$b[3] = "A"; // php is copy on write
		var_dump ($b[0]);
		var_dump ($a);
		var_dump ($b);
	}
	echo "----------------------------------\n";



?>
