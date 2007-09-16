<?php


	$b = 7;


	function &return_by_ref ()
	{
		return $GLOBALS["b"]["a"];
	}


	$x = return_by_ref ();
	$x = 8;
	var_dump ($b);
