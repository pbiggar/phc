<?php


	// A function with compile time by ref, which creates an otherwise unused
	// array index. If we shred the array index, we get the wrong answer.

	function x (&$y)
	{
		$y = 7;
	}


	x ($a[$u]);

	var_dump ($a);


?>
