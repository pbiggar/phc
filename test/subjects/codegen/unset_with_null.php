<?php

	$x = array (0 => "x", 1 => "z", "z" => "a");
	unset ($x [NULL]);

	var_dump (count ($x));
?>
