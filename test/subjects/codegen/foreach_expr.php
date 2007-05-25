<?php

	// this tests that the expression in a foreach loop is not
	// executed more than once
	$arr = array ();
	function f ()
	{
		global $arr;
		global $a;
		$arr[] = $a++;
		return $arr;
	}

	function g ()
	{
		global $arr2;
		global $a1;
		$arr2[] = $a1++;
		return $arr2;
	}

	for ($i = 0; $i < 5; $i++)
	{
		foreach (f("1", g()) as $x)
		{
			echo $x;
		}
	}

?>
