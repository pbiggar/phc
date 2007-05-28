<?php

	function f($count)
	{
		echo "f$count\n";
		return $count;
	}

	for ($i = 0; $i < 10; $i++)
	{
		switch ($i)
		{
			case f(1):
				echo "1\n";
			break;

			case f(2):
				echo "2\n";
			break;
			
			case f(3):
				echo "3\n";
			break;

			// deliberately out of order
			case f(7):
				echo "7\n";
			break;
			case f(4):
				echo "4\n";
			break;

			case f(5):
				echo "5\n";
			break;

			case f(6):
				echo "6\n";
			break;

			case f(8):
				echo "8\n";
			break;

			case f(9):
				echo "9\n";
			break;

			case f(0):
				echo "0\n";
			break;

			default:
				echo "default\n";
			break;
		}
	}

?>
