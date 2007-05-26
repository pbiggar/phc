<?php
/*
 * What happens when we unset($GLOBALS)? To set of tests, once where we unset
 * $GLOBALS from the global scope, and once where we unset it in every local
 * scope (in unset_local_global.php).
 */

	function show_global_x1()
	{
		global $x1;
		echo "x1: $x1\n";
	}

	function show_global_x2()
	{
		echo "x2: $GLOBALS[x2]\n";
	}

	function set_global_y1()
	{
		global $y1;
		$y1 = 30;
	}

	function set_global_y2()
	{
		$GLOBALS["y2"] = 40;
	}

	// First test; everything works as expected

	$x1 = 10;
	$x2 = 20;
	unset($y1);
	unset($y2);
	show_global_x1();
	show_global_x2();
	set_global_y1();
	set_global_y2();
	echo "y1: $y1\n";
	echo "y2: $y2\n";

	// Second test, after unset($GLOBALS) in the global scope
	// $x2 and $y2 now disappear, but $x1 and $y1 still work

	unset($GLOBALS);

	$x1 = 10;
	$x2 = 20;
	unset($y1);
	unset($y2);
	show_global_x1();
	show_global_x2();
	set_global_y1();
	set_global_y2();
	echo "y1: $y1\n";
	echo "y2: $y2\n";
?>
