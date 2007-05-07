<?php

	$a = array ("a" => "A", "b" => "B", 0 => 7, "a" => "Z");
	echo ("=============================================\n");
	foreach ($a as $key => $val)
	{
		var_export ($key);
		var_export ($val);
		var_export ($a);
	}

	// same again with referenced val
	echo ("=============================================\n");
	foreach ($a as $key => &$val)
	{
		var_export ($key);
		var_export ($val);
		var_export ($a);
	}

	// add some unsets
	echo ("=============================================\n");
	foreach ($a as $key => $val)
	{
		var_export ($key);
		var_export ($val);
		unset ($val);
		var_export ($a);
	}

	// and the same, by reference
	echo ("=============================================\n");
	foreach ($a as $key => &$val)
	{
		var_export ($key);
		var_export ($val);
		unset ($val);
		var_export ($a);
	}

?>
