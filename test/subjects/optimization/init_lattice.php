<?php

	// This doesnt really test very much, is just a manual calculation of what the Mark_initialized pass should do automatically.
	// - $VAR,POS -> RESULT where
	//		$VAR is a variable name,
	//		POS is use/def depending on whether $VAR is being defined or used
	//		RESULT = INIT/UNINIT/BOTTOM depending on whether VAR is initialized, uninitialized, or unknown at its use/def.

	// $x,def -> UNINIT
	$x = 0;

	// $x,use -> INIT
	print ($x);

	// $x,def -> INIT
	$x = 0;

	// $y,use -> BOTTOM
	while ($y < 20)
	{
		//$y,use -> BOTTOM
		//$y,def -> BOTTOM
		$y++;

		//$y,use -> INIT 
		print ($y);
	}

?>
