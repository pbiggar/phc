<?php
	$a = 1;
	$b =& $a;
	debug_zval_dump($b);
?>
