<?php

	register_shutdown_function ("shut");

	$x = 252;
	function shut ()
	{
		echo "shutdown function called\n";
		global $x;
		echo "this is a later reference to the die paramter to check it wasnt altered".$x."\n";
	}

	die ($x);

?>
