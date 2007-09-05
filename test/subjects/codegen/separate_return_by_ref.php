<?php

	// A function, returning a var with >1 refcount, as a copy, but who's
	// assignment is by reference.

	function my_ret ()
	{
		global $x;
		return $x; // refcount == 4
	}

	$x = 0; // refcount == 1
	$y = $x; // refcount == 2
	$z = $y; // refcount == 3

	$a =& my_ret ();
	$a = 7; // dont overwrite $x

	var_dump ($a);
	var_dump ($x);
	var_dump ($y);
	var_dump ($z);
?>	
