<?php
	$i = 0;

	for(;;)
	{
		echo "a";
		for(;;)
		{
			echo "b";
			for(;;)
			{
				echo "c";
				for(;;)
				{
					echo "d";
					break $i++;
					echo "e";
				}
				echo "f";
			}
			echo "g";
		}
		echo "h";
	}

	echo "\n";
?>
