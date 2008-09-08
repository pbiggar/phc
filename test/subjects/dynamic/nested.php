<?php
	// The function doesnt exist until the class is called.
	$x = 0;

	if (1)
	{
		function x ()
		{
			class N2
			{
				const N2 = 2;
				function y ()
				{
					var_dump (N2);
					function z ()
					{
						global $x;
						$x = 5;
					}
				}
			}
		}
	}

	x ();
	var_dump (N2::N2);

	var_dump ($x);
	$n2 = new N2();
	$n2->y ();
	var_dump ($x);

	z();
	var_dump ($x);


?>
