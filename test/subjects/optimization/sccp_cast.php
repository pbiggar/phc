<?php


	// { phc-option: -O1 --dump=outssa }
	// { phc-regex-output: !/y/ }

	function test ()
	{
		$x = (array)($y);
		var_dump ($x);
	}

?>
