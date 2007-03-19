<?php
	// "Normal" numbers
	echo -2; echo "\n";
	echo  2; echo "\n";
	echo +2; echo "\n";
	// Border line cases
	echo -2147483648; echo "\n";
	echo  2147483647; echo "\n";
	echo +2147483647; echo "\n";
	// This should be floats instead
	echo -2147483649; echo "\n";
	echo  2147483648; echo "\n";
	echo +2147483648; echo "\n";
	// Some other number systems
	echo 444; echo "\n";
	echo 0444; echo "\n";
	echo 0x444; echo "\n";
	// Big numbers as floats
	echo 0x7FFFFFFF; echo "\n";
	echo 0xFFFFFFFF; echo "\n";
	echo 0x100000000; echo "\n";
?>
