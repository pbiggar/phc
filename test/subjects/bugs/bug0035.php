<?php

	function x5()
	{
		$x = object();
		$y = "asd";
		return ($x->$y = 5);
	}

	x5();

?>
