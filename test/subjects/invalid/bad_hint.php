<?php

	function f (int $x = "string") // { Fatal error: Default value for parameters with a class type hint can only be NULL }
	{
	}

	f ("my_string");
?>
