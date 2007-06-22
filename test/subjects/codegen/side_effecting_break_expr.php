<?php

	// check that the breaking expression isnt executed more than once
	function x ()
	{
		static $x = 0;
		echo $x++;

		return 7;
	}

	break x ();

?>
