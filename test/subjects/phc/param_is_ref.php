<?php

	// Test unparsing param_is_ref

	// { phc-option: --dump=mir }
	// { phc-regex-output:  /param_is_ref \(NULL, "var_dump", 0\)/ }

	var_dump ($t->$$x[$i][$j]);

?>
