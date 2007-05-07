<?php
	$x = "y";
	$y = 5;
	$z = $$x;
	var_dump($z);

	$a = array(1,2,3);
	$b = "a";
	$c = ${$b}[1];
	var_dump($c);
?>
