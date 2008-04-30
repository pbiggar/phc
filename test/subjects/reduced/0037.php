<?php
	// Reduced with command line 'test/framework/reduce -Uvvi ashred -c--xdump=ast test/subjects/codegen/switch_functions.php'
	
	function f($count)
	{
		echo "f$count\n";
	}
	
	for($i = 0; $i < 10; $i++) {
		switch ($i) {
			case f(1):
				echo "1\n";
		}
	}
	
?>
