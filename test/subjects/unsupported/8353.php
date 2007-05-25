<?php

	$var[] = "1";
	$var[] = "2";

	foreach($var as $test)
	{
		echo $test;
	}
	reset($var); 
	echo current($var);

	$var[] = "1";
	$var[] = "2";

	//reset($var);
	foreach($var as $test)
	{
		echo $test;
		current($var);
	}
	echo current($var);


	$arr = array('a','b'); 
	foreach ($arr as $v)
		; 

	var_dump( current($arr) );

	$arr = array('a','b'); 
	foreach ($arr as $v)
		;
	reset($arr); 
	var_dump( current($arr) );

?>
