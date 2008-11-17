<?php

	// This tests out the theory that converting
	//		$x = array ();
	// to
	//		unset ($x);
	//		$x = array ($x);
	// may be unsafe (its not).


	$y =& $x;
	$x = array (1,2,3,4);

	var_dump ($y);

?>
