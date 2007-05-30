<?php
	$x = 100;
	
	while($x)
	{
		if($x > 10)
		{
			$x = $x - 5;
			$y++;
		}
		else
		{
			$x = $x - 1;
		}
	}
	
	while($x):
		$x = $x - 1;
	endwhile;
?>
