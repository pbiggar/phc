<?php

	// Check foreach loop are unparsed in the MIR

	// { phc-option: --dump=mir }
	// { phc-regex-output: foreach_reset\(\$\w+, ht_iterator\d+\); }

	foreach ($x as $y)
	{
	}
?>
