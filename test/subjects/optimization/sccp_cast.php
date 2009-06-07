<?php


	// { phc-option: -O1 --dump=codegen }
	// Actually, casts dont have rvalues, so its not that godo an idea.
	// phc-regex-output: !/y/

	function test ()
	{
		$x = (array)($y);
		var_dump ($x);
	}

?>
