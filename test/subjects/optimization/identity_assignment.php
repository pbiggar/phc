<?php

	$x = array ("asd", array (1, 2, NULL));

//	foreach (array (1,2,3) as $i)
//	{
		$x = $x;
		$x[$i] = $x[$i];
		$x = &$x;
		$x[$i] = &$x[$i];
//	}

?>
