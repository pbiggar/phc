<?php

	// { phc-option: -O1 --dump=outssa }
	// { phc-regex-output: !/x/ }
	function test ()
	{
		$y = ++$x;
		var_dump ($y);
	}

	test ();

?>
