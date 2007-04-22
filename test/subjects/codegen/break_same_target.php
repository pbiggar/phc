<?php

	// both breaks jump to the same spot
	for ($i = 0; $i < 10; $i++)
	{
		if ($i > 3)
		{
			for ($j = 0; $j < 10; $j++)
			{
				if ($j > 6)
					break 2;
				var_dump ($j);
			}
		}
		var_dump ($i);
		if ($i == 9)
			break 1;
	}
?>
