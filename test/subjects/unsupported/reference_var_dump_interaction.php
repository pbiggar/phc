<?php

	$a = array ("a" => "A", "b" => "B", 0 => 7, "a" => "Z");
	echo ("=============================================\n");
	foreach ($a as $key => $val)
	{
		var_dump ($key);
		var_dump ($val);
		var_dump ($a);
	}

	// same again with referenced val
	echo ("=============================================\n");
	foreach ($a as $key => &$val)
	{
		var_dump ($key);
		var_dump ($val);
		var_dump ($a);
	}

	// add some unsets
	echo ("=============================================\n");
	foreach ($a as $key => $val)
	{
		var_dump ($key);
		var_dump ($val);
		unset ($val);
		var_dump ($a);
	}

	// and the same, by reference
	echo ("=============================================\n");
	foreach ($a as $key => &$val)
	{
		var_dump ($key);
		var_dump ($val);
		unset ($val);
		var_dump ($a);
	}

?>
