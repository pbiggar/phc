<?php

	// This shows that 'global' statements do affect the global symbol table,
	// and cannot be eliminated.
	$y = 5;

	f ();

	$x = compact ('y', 'c');

	var_dump ($x);

	function f ()
	{
		global $c;
	}

?>
