<?php

	// Check no output for a fake pass

	//	options :: out_regex :: err_regex :: exit_code :: no subject
	// { --debug=ast ::  ::  :: 0 :: false }

	function y ($x)
	{
		$y = $x++;
	}
?>
