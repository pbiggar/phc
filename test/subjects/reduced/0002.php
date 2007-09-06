<?php
	// Reduced from test/subjects/codegen/functioncalls_evald_functions.php with phc arguments "--run=plugins/tools/debug_zval.la --dump=plugins/tools/debug_zval.la"
	function fun_r(&$x) 
	{ 
		$x = 'x'; 
	}
	fun_r($r);
	debug_zval_dump($r);
?>
