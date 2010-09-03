<?php

	// Any trace of 'foreach_' should be removed
	// { phc-option: -O1 --dump=codegen }
	// { phc-regex-output: !/foreach_/ }

	function x ()
	{
		$x = array (1,2,3,4);
		foreach ($x as $y)
		{
			$j = $y;
		}
	}

	x();

?>
