<?php

	// Test the --stats option. It should trigger for constant-folding.

	// { phc-option: --stats }
	// { phc-regex-output: /^folded_bin_op|1|$/ }
	$x = 2 + 5;
?>
