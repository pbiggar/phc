<?php
	$x = array(1 => "a", 2 => "b", 3 => "c", 4 => "d");

	foreach($x as &$y => &$z) // {  phc-error: Key element cannot be a reference }
	{
		echo "$y => $z\n";
	}
?>
