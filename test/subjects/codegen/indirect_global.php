<?php
// Indirect (variable variable) reference to globals.
	function f()
	{
		$x = "GLOBALS";
		${$x}["a"] = 1;
		$GLOBALS["b"] = 2;
	}

	f();
	// var_dump($a); // disabled because PHP doesn't like it (bug in PHP?)
	var_dump($b);

	$x = "GLOBALS";
	${$x}["c"] = 3;
	$GLOBALS["d"] = 4;
	var_dump($c);
	var_dump($d);
?>
