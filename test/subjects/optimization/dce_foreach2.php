<?php

	// Foreach should be kept
	// { phc-option: -O1 --dump=codegen }
	// { phc-regex-output: /foreach_reset/ }
	// { phc-regex-output: /foreach_next/ }
	// { phc-regex-output: /foreach_get_val/ }

	function x ()
	{
		$x = array (1,2,3,4);
		foreach ($x as $y)
		{
			echo $y;
		}
	}

	x();

?>
