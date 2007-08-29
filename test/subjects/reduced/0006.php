<?php
	function fun($x) 
	{ 
		$x = 'x'; 
	}
	
	$g = 60;
	$h = $g;
	fun(&$h);
	var_export($h);
?>
