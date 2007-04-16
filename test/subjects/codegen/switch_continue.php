<?php

	for ($x = 0; $x < 10; $x++)
	{
		switch ($x)
		{
			case 0:
				echo "0\n";
				break;
				echo "x\n";
			case 1:
				echo "1\n";
				break;
				echo "x\n";
			case 3: // for the hell of it
			case 2:
				echo "2\n";
				break;
				echo "x\n";
			case 4:
				echo "4\n";
				continue; // the same as break
				echo "x\n";
			case 5:
				echo "5\n";
				continue 2; // contiune the loop
				echo "x\n";
		}
		echo "done switch\n";
	}
?>
