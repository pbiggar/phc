<?php

	// Reported by Viesturs Ducens

	if (!defined('dummy'))
	{
		echo "IS \n";
		include_once ("./test/subjects/parsing/included_cc1.php");
		include_once ("./test/subjects/parsing/included_cc2.php");
		echo "IS2 \n";
	}
	else
	{
		echo "NOT \n";
	}

?>
