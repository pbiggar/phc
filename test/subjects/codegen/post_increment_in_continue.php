<?php
	$i = 0;
	
	do
	{
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
						continue $i++;
						echo "e";
					}
					echo "f";
				}
				echo "g";
			}
			echo "h";
		}
	} while(False);

	echo "\n";
?>
