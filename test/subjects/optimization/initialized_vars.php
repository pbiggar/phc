<?php


	$x = 5;

	function unset_it (&$var)
	{
		var_dump ($var);
		unset ($var);
		var_dump ($var);
	}

	unset_it ($x);
	
	var_dump ($x);

?>
