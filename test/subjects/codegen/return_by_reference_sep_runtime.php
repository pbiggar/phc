<?php
// Return a variable by reference, where the variable is part of a 
// copy-on-write set

	$a = 5;
	$b = $a;

	function f()
	{
		return $GLOBALS["b"];
	}

	$c =& f();
	$c = 6;

	var_export($a);
	var_export($b);
	var_export($c);
?>
