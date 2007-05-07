<?php

	// PHP bug 29992 addresses this issue
	$x = array(4 => "d");

	foreach($x as &$y)
	{
	}
	// at this point, $y references "d"

	foreach($x as $y => &$z)
	{
		// every assignment to $y assigns to $x[4] (ie overwrites "d")
		echo "$y => $z\n";
	}
?>
