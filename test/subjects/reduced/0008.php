<?php
	
	function set_global_y1()
	{
		global $y1;
		$y1 = 30;
	}
	
	// Second test, after unset($GLOBALS) in the global scope
	// $x2 and $y2 now disappear, but $x1 and $y1 still work
	
	unset($GLOBALS);
	$TSe10 = set_global_y1();
	$TSp5 = printf($TLE31, $TLE25);
?>
