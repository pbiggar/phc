<?php
$a=array("1","2");
$b=&$a;//*
foreach($a as $i){
	print($i);
	foreach($a as $p);//*
}

?>
