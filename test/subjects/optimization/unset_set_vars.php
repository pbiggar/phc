<?php

	$x = 5;
	$y =& $x;
	unset ($x);
	var_dump ($x);
	var_dump ($y);
	unset ($y);
	var_dump ($x);
	var_dump ($y);

?>
