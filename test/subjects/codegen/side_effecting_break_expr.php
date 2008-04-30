<?php

	// check that the breaking expression isnt executed more than once
	function x ()
	{
		static $x = 0;
		echo $x++;

		return 0;
	}

	do
	{
		break x ();
		echo "error\n";
	}
	while (false);

?>
