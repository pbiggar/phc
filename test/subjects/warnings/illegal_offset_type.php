<?php

	// TODO also check arrays
	// TODO should this really only be a warning?

	class A
	{
	}

	$x = array (new A () => 5); // { Warning: Illegal offset type }
	$x = array (array (5) => 5); // { Warning: Illegal offset type }
?>
