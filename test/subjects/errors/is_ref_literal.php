<?php

	// Add a check for a syntax error
	function x (&$y)
	{
		$y = 10;
	}


	x (&"asd"); // { phc-error:  syntax error, unexpected T_STRING, expecting IDENT or VARIABLE or '$' }
?>
