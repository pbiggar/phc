<?php

	// this adds an element to $x. If we add
	// a temporary without a reference, we
	// get wrong code (nothing is added)

	function foo (&$y)
	{
		$y = 7;
	}
	
	$x = array ();
	foo ($x[0]);
	var_dump($x);
?>
