<?php
	//error: tests/subjects/general/foreach_error2.php:7: error: Variable name expected
	//return: 2

	$x = array(1 => "a", 2 => "b", 3 => "c", 4 => "d");
	
	foreach($x as f())
	{
		echo "bold";
	}
?>
