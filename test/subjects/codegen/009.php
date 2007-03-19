<?php
	$x = 5;
	var_dump($x["a"]);
	var_dump($x);
	$x["a"] = 6;
	var_dump($x["a"]);
	var_dump($x);
	unset($x);
	$x["a"] = 6;
	var_dump($x["a"]);
	var_dump($x);
?>
