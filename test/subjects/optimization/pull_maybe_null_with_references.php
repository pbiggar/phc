<?php

	if ($argv[2])
	{
		$x =& $y;
		$x = 5;
	}
	else
	{
		$x = 5;
	}

	var_dump ($x);
	var_dump ($y);

?>
