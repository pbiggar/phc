<?php
	$a = 5;
	$b[1] =& $a;
	$b[1] = 6;
	var_dump($a);
	var_dump($b);
?>
