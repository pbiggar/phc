<?php

	// I'm not sure what this means, but its not the result I expected.

	function f()
	{
		static $x = 1;
		var_dump($x);
		$x =& $GLOBALS["y"];
		var_dump($x);
	}

	$y = 5;
	f();
	f();
	$y = 6;
	f();
?>
