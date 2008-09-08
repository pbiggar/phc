<?php

	function x ()
	{
		echo "x\n";
		function y ()
		{
			echo "y\n";
			function z()
			{
				echo "z\n";
			}
		}
	}

	x ();
	y ();
	z ();

?>
