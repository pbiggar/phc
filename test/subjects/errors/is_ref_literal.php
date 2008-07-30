<?php

	// Add a check for a syntax error
	function x (&$y)
	{
		$y = 10;
	}


	x (&"asd");
?>
