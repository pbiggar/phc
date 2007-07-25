<?php

	function x ()
	{
		echo "x\n";
		return 7;
	}

	for ($i = 0; $i < 5; $i++)
	{
		break x ();
	}

?>
