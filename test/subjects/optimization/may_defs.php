<?php

	// This must-def $x
	$y =& $x[5];

	if ($argc == 5)
		$y = 5;

	var_dump ($x);




	// This must-def $x2
	f ();

	function f ()
	{
		global $x2;
		$x2 = 6;
	}

	var_dump ($x2);


	// This must-def $x3
	function x (&$x) {}
	f ($x3);

	var_dump ($GLOBALS);
?>
