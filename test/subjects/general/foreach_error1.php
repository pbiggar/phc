<?php
	//error: tests/subjects/general/foreach_error1.php:7: error: Key element cannot be a reference
	//return: 3

	$x = array(1 => "a", 2 => "b", 3 => "c", 4 => "d");

	foreach($x as &$y => &$z)
	{
		echo "$y => $z\n";
	}
?>
