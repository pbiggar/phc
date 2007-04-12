<?php
	$c = 5;
	$a = 1;
	$b = $a;
	$c =& $a;
	var_dump($a);
	var_dump($b);
	var_dump($c);
?>
