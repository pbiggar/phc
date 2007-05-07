<?php
$a=array(0,1,2,3,4,5,6);
foreach ($a AS $val)	{
	print $val;
	list(,$val)=each($a);
	list(,$val)=each($a);
	next($a);
	print $val;  }

?>
