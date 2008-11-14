<?php

	// { phc-option: -O1 --dump=outssa }
	// { phc-regex-output: !/[xy]/ }

	function test ()
	{
		$y = 10;
		$x = 1; 
		$x = 0; 
		echo "$y\n";
	}
?>
