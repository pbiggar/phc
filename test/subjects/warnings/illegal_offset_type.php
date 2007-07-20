<?php

	// TODO also check arrays

	class A
	{
	}

	// check for error
	$x = array (new A () => 5); // { Warning: Illegal offset type }

?>
