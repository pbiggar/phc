<?php
	// Now try it nested

	// Nothing defined yet
	if (1)
	{
		function x ()
		{
			interface N2
			{
				const N2 = 2;
			}
		}
	}

	var_dump (N2::N2);
	x ();

?>
