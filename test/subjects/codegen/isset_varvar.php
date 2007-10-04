<?php
	// isset on variable variables
	$y = "x";

	if(isset($$y))
		echo "x is set (1)\n";
	
	$x = 1;
	
	if(isset($$y))
		echo "x is set (2)\n";
?>
