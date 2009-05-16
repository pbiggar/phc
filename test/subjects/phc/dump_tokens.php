<?php

	// Check --dump-tokens has some output
	// { phc-option: --dump-tokens }
	// { phc-regex-output: /\d+: keyword->token/ }
	// { phc-regex-output: /\d+: T_STRING/ }
	// { phc-regex-output: /\d+: SIMPLE_OP ;/ }
	// { phc-regex-output: /\d+: ';'/ }

	echo "test";
?>
