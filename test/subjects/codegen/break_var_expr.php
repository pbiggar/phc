<?php
	
	// a non-constant expression

	for ($i =0; $i < 10; $i++) 
	{ 
		for ($j =0; $j < 10; $j++) 
		{
			for ($k =0; $k < 10; $k++) 
			{
				break "a string";
				var_dump ("k$k");
			}
			var_dump ("j$j");
		}
		var_dump ("i$i");
	}
?>
