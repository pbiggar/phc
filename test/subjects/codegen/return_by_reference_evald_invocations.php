<?php
/*
 * See return_by_reference_compiled.php; eval'd function invocations. 
 */

	function f()
	{
		return $GLOBALS["a"];	
	}
	
	function &g()
	{
		return $GLOBALS["a"];
	}

	eval('$a = 5;');
	eval('$b = f();');
	eval('$b = $b + 1;');
	eval('var_export($a);');
	eval('var_export($b);');

	eval('$a = 5;');
	eval('$c = g();');
	eval('$c = $c + 1;');
	eval('var_export($a);');
	eval('var_export($c);');

	eval('$a = 5;');
	eval('$d =& f();');
	eval('$d = $d + 1;');
	eval('var_export($a);');
	eval('var_export($d);');

	eval('$a = 5;');
	eval('$e =& g();');
	eval('$e = $e + 1;');
	eval('var_export($a);');
	eval('var_export($e);');
?>
