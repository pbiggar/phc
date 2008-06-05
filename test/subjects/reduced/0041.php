<?php
	// Reduced with command line 'test/framework/reduce -v -v -i AST-to-HIR -c--xdump=ast test/subjects/codegen/switch_continue.php'
	
	for($x = 0; $x < 10; $x++) {
		switch ($x) {
			case 5:
				// contiune the loop
				continue 2;
		}
		echo "done switch\n";
	}
?>
