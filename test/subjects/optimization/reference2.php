<?php

	// Can be more than 1 storage node
	if ($argc == 2)
		$x = array ();
	else
		$x = new Object;

	$x["f"] =& $y;

	var_dump ($x["f"])


	$y = 5;

	var_dump ($x);

?>
