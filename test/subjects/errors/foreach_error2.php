<?php

	$x = array(1 => "a", 2 => "b", 3 => "c", 4 => "d");
	
	foreach($x as f()) // { phc-error: Variable name expected }
	{
		echo "bold";
	}
?>
