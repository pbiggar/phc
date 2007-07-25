<?php

	for ($i = 0; $i < 7; $i++)
	{
		foreach (array (0,1) as $x)
		{
			while ($x > 0)
			{
				break 17; // { Warning: Cannot break 17 levels }
				$x--;
			}
		}
	}
?>
