<?php

	class Integer {}
	class My_int extends Integer {}

	$x = new My_int ;
	$z = new My_int ;
	$x->f = 5;

	var_dump ((Integer) ($x));
	var_dump ((Integer) ($z));

?>
