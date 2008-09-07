<?php

	echo $f;
	$f = 6;
	echo $f;
	include "included_recursive2.php";
	echo $f;

	echo (get_include_path());

?>
