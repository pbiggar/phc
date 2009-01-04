<?php
	// Simple field access
	eval('$c = new StdClass(); $c->a = 1;');
	var_dump($c->a);
?>
