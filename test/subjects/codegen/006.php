<?php
	eval("\$a = 5;");
	eval("\$b = \$a;");
	eval("\$d = \$c;"); // c isnt initted yet
	$b = $b + 1;
	var_dump($a);
	var_dump($b);
	var_dump($c);
	var_dump($d);
?>
