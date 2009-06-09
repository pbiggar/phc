<?php

	$x[$argc] = 5;

	var_dump ($x[0]);

	$z[$argc] = 5;
	$y =& $z[0];

	var_dump ($x[0]);
	var_dump ($x);
	var_dump ($y);
	var_dump ($x);

?>
