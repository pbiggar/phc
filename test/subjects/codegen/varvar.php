<?php
	$a = 5;

	$arr[1] = "a";
	var_dump(${$arr[1]});
	
	${$arr[1]} = 6;
	var_dump($a);
?>
