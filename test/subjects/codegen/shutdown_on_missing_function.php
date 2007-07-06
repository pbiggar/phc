<?php

	// if the error exits improperly, the shutdown function wont be called.
	register_shutdown_function ("shut");

	function shut ()
	{
		echo "shutdown function called\n";
	}

	// trigger an undefined function error
	f ();

?>
