<?php
	$query1 = 
		" SELECT " . $a . 
		" FROM " . $b .
		" WHERE " . $c . " GROUPBY " . $d;

	$query2 =
		  " SELECT " . $a
		. " FROM " . $b
		. " WHERE " . $c . " GROUPBY " . $d;

	echo $query1; echo $query2; 
?>
