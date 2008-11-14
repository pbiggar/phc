<?php


	// { phc-option: -O1 --dump=outssa }
	// Actually, casts dont have rvalues, so its not that godo an idea.
	// phc-regex-output: !/y/

	function test ()
	{
		$x = (array)($y);
		var_dump ($x);
	}

?>
