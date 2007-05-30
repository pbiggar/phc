<?php

	$x = 5;

	while($x)
	{
		$x = $x - 1;
		if($x == 3)
		{
			continue 3;
		}
		printf("x is $x");
	}
		  
?>
