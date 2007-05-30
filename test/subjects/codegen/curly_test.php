<?php
	$a = array(1,2,3);
	$b = "a";
	$c = ${$b}[1]; // if the curlies here are lost, we get the wrong answer
	var_dump($c);
?>
