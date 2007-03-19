<?php

$x = 100;

function whiletest()
{
	
	$x = 200;
	
	for($i = 0; $i < 5; $i++)
	{
	
		echo "x: $x\n";
		global $x;

	}

}

whiletest();

?>
