<?php

	// this would be printed in hex with the bug

	$a = "a $b c";
	$a = "\001\002 $b \003\004";
	$a = "\001\002 $b \003\004";
	$a = "\001\002 $b \003\004";
	$a = "\001\002 $b \003\004";
	$a = "\001\002 $b \003\004";
	$a = "\001\002 $b \003\004";
	$a = "\001\002 $b \003\004";
	$a = "\001\002 $b \003\004";
	$a = "\000\001\002 $b \003\004\005" . 29;

	// this bug is tickled when the line_numbers.so plugin tries to print an
	// integer. im not sure why it didnt fail before, and I cant seem to make it
	// fail otherwise
	
?>
