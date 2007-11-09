<?php

require ("scalar_array.php");

class A
{
	// the PHP docs say an object converts to the string "Object", but it doesnt
	// look like it
	function __toString()
	{
		return "a";
	}
}

$scalar_array[] = new A ();

foreach ($scalar_array as $y)
{
	var_dump ($y);

	$x = (int) $y;
	var_dump ($x);

	$x = (integer) $y;
	var_dump ($x);

	$x = (float) $y;
	var_dump ($x);

	$x = (real) $y;
	var_dump ($x);

	$x = (double) $y;
	var_dump ($x);

	$x = (string) $y;
	var_dump ($x);

	$x = (array) $y;
	var_dump ($x);

	$x = (object) $y;
	var_dump ($x);

	$x = (bool) $y;
	var_dump ($x);

	$x = (boolean) $y;
	var_dump ($x);

	$x = (unset) $y;
	var_dump ($x);

	# some variations

	$x = (BOOLean) $y;
	var_dump ($x);

	$x = (       string     ) $y;
	var_dump ($x);

	$x = (				string) $y;
	var_dump ($x);

}
?>
