<?php

	function f()
	{
		// pure, but need IPO for that
		return 7;
	}

	// Change potentially side-effecting expressions into Eval_exprs
	$x = f();

?>
