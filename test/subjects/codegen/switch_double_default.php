<?php

	// In the case of multiple defaults, use the last one.
	// Note that defaults can fall-through to other edges.
	switch (6)
	{
		default:
			echo "default1\n";
		default:
			echo "default2\n";
		case 7:
			echo "seven\n";
	}

?>
