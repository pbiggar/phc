<?php
/*
 * See return_by_reference_compiled.php; eval'd function definitions.
 */

	eval('function f()
	{
		return $GLOBALS["a"];	
	}');
	
	eval('function &g()
	{
		return $GLOBALS["a"];
	}');

	$a = 5;
	$b = f();
	$b = $b + 1;
	var_export($a);
	var_export($b);

	$a = 5;
	$c = g();
	$c = $c + 1;
	var_export($a);
	var_export($c);

	$a = 5;
	$d =& f();
	$d = $d + 1;
	var_export($a);
	var_export($d);

	$a = 5;
	$e =& g();
	$e = $e + 1;
	var_export($a);
	var_export($e);
?>
