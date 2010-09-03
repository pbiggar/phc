<?php

	// Aliasing and references
	$x =& $GLOBALS;
	$y = 5;
	$z = 4;

	function a ()
	{
		global $x;


		// overwrite GLOBALS
		$x = array ();
		var_dump ($GLOBALS);

		// this ignores GLOBALS
		global $y, $z;

		$y = 3;
		$z = 2;

		// $y and $x arent set in GLOBALS
		var_dump ($x);
	}

	a ();

	// $z has been reset
	var_dump ($z);

	// GLOBALS is still empty
	var_dump ($GLOBALS);

?>
