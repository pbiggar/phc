<?php

	define (X, 5);

	// { phc-error: syntax error, unexpected ';', expecting O_COLONCOLON }
	$y =& X;

?>
