<?php
	$arr1 = array(1,2,3);
	unset($arr1[1]);
	var_export($arr1);

	$arr2 = array("a" => 1, "b" => 2, "c" => 3);
	unset($arr2["b"]);
	var_export($arr2);
?>
