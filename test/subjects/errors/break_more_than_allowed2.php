<?php

	for ($i = 0; $i < 7; $i++)
	{
		foreach (array (0,1) as $x)
		{
			while ($x > 0)
			{
				break 17; // { phc-error: Cannot break/continue 17 levels }
				$x--;
			}
		}
	}
?>
