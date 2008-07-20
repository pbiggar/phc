<?php
	// Reduced with command line 'test/framework/reduce -v test/subjects/codegen/foreach_key_val.php'
	$a = array (0 => NULL, 'a' => NULL);
	foreach ($a as $key => &$val) {
	}
	foreach ($a as $key => $val) {
		unset($val);
	}
?>
