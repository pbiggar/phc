<?php

	try
	{
		break; // { Error: Cannot break/continue 1 levels }
		echo "asd\n";
	}
	catch (Exception $e)
	{
	}
	echo "exitted safely\n";

?>
