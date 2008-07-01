<?php
	// Reduced with command line 'test/framework/reduce -v -i AST-to-HIR -c--xdump=ast test/subjects/codegen/shred_op_assign_target.php'

	// The correct result for this is:
/*
		$TSr0 =& $$a;
		$TSr1 = $$c;
		$TSr2 = $$d;
		$TSt3 =& $TSr0->$b;
		$TSi4 =& $TSt3[$TSr1];
		$TSr5 = $$f;
		$TSi6 = $e[$TSr5];
		$TSr7 = $$h;
		$TSi8 = $g[$TSr7];
		$TSr9 = $$TSi8;
		$TSi10 =& $TSi4[$TSr2];
		$TSi11 = $TSi4[$TSr2];
		$TSt12 = $TSi11->$TSi6;
		$TLE13 = ($TSt12 + $TSr9);
		$Tx =& $TSi10->$TSi6;
		$Tx = $TLE13;
		var_dump($x1);
*/

	
	$a = "x1";
	$b = "x2";
	$e = "x5";
	
	// Whats the most convoluted pre_op/op-assignment I can do?
	$$a->{$b}[$$c][$$d]->{$e[$$f]} += ${$g[$$h]};
	
	var_dump($x1);
?>
