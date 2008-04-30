<?php

	$x = 7;
	switch ($x)
	{
		case 7:
			f ();
			break;
		case 8:
			while ($x != 0)
			{
				if ($x == 5)
					break 2;
			}
			break;
		default:
			break;
	}

	// as an if statement

	$x = 7;
	do
	{
		if ($x == 7 || $x == 8)
		{
			while ($x != 0)
			{
				if ($x == 5)
				{
					break 2;
				}
			}
		}
	}
	while (0);

?>
