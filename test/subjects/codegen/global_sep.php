<?php
// Global creates a reference, and must thus separate copy-on-write arguments

	$a = 5;
	$b = $a;

	function f()
	{
		global $b;
		$b = $b + 1;
	}

	f();
	
	var_export($a);
	var_export($b);
?>
