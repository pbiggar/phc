<?php

	// { phc-option: -O1 --dump=outssa }
	// { phc-regex-output: !/\$[abcd]/ }
	// { phc-regex-output: !/[1]/ }
	$d = 1;
	$c = $d;
	$b = $c;
	$a = $b;

?>
