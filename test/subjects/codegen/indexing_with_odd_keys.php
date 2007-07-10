<?php
	$arr = array(
		10 => "a",
		2.345 => "b",
		True => "c",
		False => "d",
		NULL => "e",
		"f" => "g");
	
	var_export($arr);

	var_dump ($arr[10]);
	var_dump ($arr[2.345]);
	var_dump ($arr[true]);
	var_dump ($arr[False]);
	var_dump ($arr[NULL]);
	var_dump ($arr["f"]);
?>
