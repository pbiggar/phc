<?php

	$x = 1;

	switch ($x)
	{
		case 0:
			echo "not done\n";
			break;

		case (f() ? g () : h ()):
			echo "done\n";
			break;

		default:
			echo "default\n";
	}


	function f () { echo "f\n"; }
	function g () { echo "g\n"; }
	function h () { echo "h\n"; }

?>
