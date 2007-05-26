<?php
// Indirect (variable variable) reference to globals.
	$x = "GLOBALS";
	${$x}["a"] = 5;
	var_dump($a);
?>
