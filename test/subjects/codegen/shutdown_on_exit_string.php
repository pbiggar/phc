<?php

	register_shutdown_function ("shut");

	function shut ()
	{
		echo "shutdown function called\n";
	}

	die ("asd");

?>
