<?php

	// { phc-option: -O1 --dump=opt }
	// { phc-regex-output: !/x/ }
	// { phc-regex-output: !/y/ }
	$y = 10;
	$x = 1; 
	$x = 0; 
	echo "$y\n";
?>
