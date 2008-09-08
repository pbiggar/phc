<?php

	$x = false;
	$y = true;
	$z = 5;
	$w = 5.7;

	$a = 1;

	$x[] =& $a;
	$y[] =& $a;
	$z[] =& $a;
	$w[] =& $a;

	var_dump ($x);
	var_dump ($y);
	var_dump ($z);
	var_dump ($w);
?>
