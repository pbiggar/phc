<?php
	// Reduced with command line 'test/framework/reduce -v -u -i mir test/subjects/codegen/foreach_shocking.php'
	$x = array ('d');
	foreach ($x as &$y) {
	}
	foreach ($x as $y => &$z) {
		echo $z;
	}
?>
