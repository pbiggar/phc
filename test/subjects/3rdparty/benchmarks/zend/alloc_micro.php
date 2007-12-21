<?php
	$start = microtime(true);

	for($i=0; $i< 1000000; $i++) 
	{
		$x[$i] = 'xxxxx';
	}

	$stop = microtime(true);
	print ($stop-$start)."\n";
?>
