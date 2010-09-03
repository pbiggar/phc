<?php
	$x = 5;
	
	if ( rand () )
	{
		$y =& $x;
	}
	else
	{
		$x = 8;
	}
	$y = 7;
	var_dump ($x);
	var_dump ($y);
?>
