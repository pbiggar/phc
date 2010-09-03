<?php

	// { phc-option: -O1 --dump=codegen }
	// { phc-regex-output: !/x/ }
	function test ()
	{
		$y = ++$x;
		var_dump ($y);
	}

	test ();

?>
