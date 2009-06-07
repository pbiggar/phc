<?php

	// A simple example I've done out by hand. Taken from bench_simple_ucall.

	function hallo($a)
	{
	}

	function simpleucall() 
	{
		for ($i = 0; $i < 10; $i++) 
		{
			hallo("hallo");
			$flags[$i] = $a[$i];
		}
	}

	simpleucall ();

?>
