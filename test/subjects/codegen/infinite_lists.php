<?php

	$x[0] = $x;
	var_dump ($x);

	$y[0] =& $y;
	var_dump ($y);

?>
