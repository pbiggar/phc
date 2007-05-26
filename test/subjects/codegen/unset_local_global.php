<?php
/*
 * See unset_global_global.php; here, we can unset $GLOBALS at the start
 * of every function (locally).
 */

	function show_global_x1()
	{
		unset($GLOBALS);
		global $x1;
		echo "x1: $x1\n";
	}

	function show_global_x2()
	{
		unset($GLOBALS);
		echo "x2: $GLOBALS[x2]\n";
	}

	function set_global_y1()
	{
		unset($GLOBALS);
		global $y1;
		$y1 = 30;
	}

	function set_global_y2()
	{
		unset($GLOBALS);
		$GLOBALS["y2"] = 40;
	}

	// Again, $x2 and $y2 disappear

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
