<?php

class A
{
	// the PHP docs say an object converts to the string "Object", but it doesnt
	// look like it
	function __toString()
	{
		return "a";
	}
}

foreach (array (0, 3, "asd", new A()) as $y)
{
	var_dump ($y);
	$x = (int) $y;
	var_dump ($x);
	$x = (float) $y;
	var_dump ($x);
	$x = (string) $y;
	var_dump ($x);
	$x = (array) $y;
	var_dump ($x);
	$x = (object) $y;
	var_dump ($x);
	$x = (bool) $y;
	var_dump ($x);
	$x = (unset) $y;
	var_dump ($x);
}
?>
