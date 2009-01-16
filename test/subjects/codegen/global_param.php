<?php

	// PHP initializes a function GLOBALS _before_ its parameters
	$a = 6;

	function a ($GLOBALS)
	{
		var_dump ($GLOBALS);
		var_dump ($GLOBALS["a"]);
	}

	a (5);

?>
