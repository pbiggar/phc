<?php

	function f () { return 7; }
	class A {}

	// An array index is an AST_expression. Check all the types we think are allowed.
	// assignment
	$x = array (($z = 12) => 13);
	var_dump ($x);

	// list assignment (list assignments are generally to arrays, so it would
	// evaluate to an array. But not here.)
	$x = array ((list ($z) = 6) => 14);
	var_dump ($x);

	// cast
	$x = array (($z = (int)("5")) => 15);
	var_dump ($x);

	// unary op
	$x = array ((!$z) => 16);
	var_dump ($x);

	// bin op
	$x = array (($z + $c) => 17);
	var_dump ($x);

	// conditional_expr
	$x = array (($z ? $y : $z) => 18);
	var_dump ($x);

	// ignore_errors
	$x = array (@$z => 19);
	var_dump ($x);

	// constant
	$x = array (FOObar => 20);
	var_dump ($x);

	// instanceof
	$x = array (($z instanceof int) => 21);
	var_dump ($x);

	// pre_op
	$x = array ((++$z) => 22);
	var_dump ($x);

	// post_op
	$x = array (($z++) => 23);
	var_dump ($x);

	// array - not allowed
//	$x = array (array () => 24);
//	var_dump ($x);

	// method_invocation
	$x = array (f() => 24);
	var_dump ($x);

	// new - not allowed
//	$x = array (new A () => 24);
//	var_dump ($x);

	// clone - clones objects only, so not allowed
//	$x = array (clone ($z) => 25);
//	var_dump ($x);

	// literal
	$x = array (1 => 26, false => 27, "asd" => 28, 1.34 => 29);
	var_dump ($x);

?>
