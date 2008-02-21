<?php

	function f ()
	{
		echo "f called\n";
		return 8;
	}

	switch (8)
	{
		default:
			echo "def";
		case 8:
			echo "8 called1\n";
		case 8:
			echo "8 called2\n";
		case f ():
			echo "8 called3\n";
			break;
		case 8:
			echo "8 called4\n";
			break;
	}

?>
