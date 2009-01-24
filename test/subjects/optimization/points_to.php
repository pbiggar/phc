<?php

	// A difficult example, illustrating a lot of the complexities.

	for ($i = 0; $i < 10; $i++)
	{
		$x = $i;
		if ($argc != 2)
			$y =& $x;
		else
			; // $y is uninit

		$y = array ();
		$y[] = 7;

		$z = $x[5];
	}

	print "$z\n";

?>
