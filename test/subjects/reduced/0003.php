<?php
	function fun($x) 
	{
		$x = 'x';
	}
	fun(&$p);
	var_export($p);
?>
