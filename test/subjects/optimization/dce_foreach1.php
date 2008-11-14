<?php

	// Any trace of 'foreach' should be removed
	// phc-option: -O1 --dump=generate-c
	// phc-out-regex: !/foreach/

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
