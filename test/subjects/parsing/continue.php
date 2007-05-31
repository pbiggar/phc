<?php

	$x = 5;

	while($x)
	{
		$x = $x - 1;
		if($x == 3)
		{
			continue 1;
		}
		printf("x is $x");
	}
		  
?>
