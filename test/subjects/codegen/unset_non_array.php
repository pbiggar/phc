<?php

	$x = 0;
	unset ($x[5]);

	var_dump ($x);

	$y = array (6);
	unset ($y[0][5]);
	var_dump ($y);
	unset ($y[0][0]);
	var_dump ($y);
?>
