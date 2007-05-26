<?php
/*
 * The first example does not work as expected, the second does. The reason is
 * (I think) that "global $x" makes $x a reference to some global variable, and
 * $x =& $a then re-assigns that (local) reference to point to the (local)
 * variable. OTOH, in the second example, we change the $GLOBALS array and
 * re-assign the _global_ reference to point to $y. 
 *
 * Example due to cellog@users.sourceforge.net and danno@wpi.edu
 */

	function f()
	{
		$a = 10;
		global $x;
		$x =& $a;
	}

	function g()
	{
		$b = 20;
		$GLOBALS["y"] =& $b;
	}

	f();
	var_dump($x);

	g();
	var_dump($y);
?>
