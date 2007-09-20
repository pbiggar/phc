<?php

	$x = 7;
	function y ()
	{
		unset ($GLOBALS ["x"]);
	}

	y ();

	var_dump ($x);

?>
