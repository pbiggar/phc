<?php

	// TODO also check arrays
	// TODO Hard to say if this should be an error or a warning. Its only a run-time
	// warning in PHP, and you're code will continue running, but its definately a semantic error.

	class A
	{
	}

	$x = array (new A () => 5); // { phc-error: Illegal offset type }
?>
