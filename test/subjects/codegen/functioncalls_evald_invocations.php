<?php
/*
 * Like functioncalls_compiled, but using eval'd function invocations.
 */

	function fun($x) { $x = 'x'; }
	function fun_r(&$x) { $x = 'x'; }
	function &fun_rr($x) { return $x; }

	// Test proper calling conventions in simple cases

	eval('$a = 10;');
	eval('fun($a);');
	eval('var_export($a);');

	eval('$b = 20;');
	eval('fun(&$b);');
	eval('var_export($b);');

	eval('$c = 30;');
	eval('fun_r($c);');
	eval('var_export($c);');

	eval('$d = 40;');
	eval('fun_r(&$d);');
	eval('var_export($d);');

	eval('$d1 = 41;');
	eval('fun_rr(&$d1);');
	eval('var_export($d1);');

	eval('$d2 = 42;');
	eval('fun_rr(&$d2);');
	eval('var_export($d2);');

	eval('echo "\n";');

	// Same as before, but the variable now passed in is part of a
	// copy-on-write set. In all cases where a pass-by-reference is involved,
	// only one of the two variables should be changed.

	eval('$e = 50;');
	eval('$f = $e;');
	eval('fun($f);');
	eval('var_export($e);');
	eval('var_export($f);');
	eval('$f = \'y\';');
	eval('var_export($e);');
	eval('var_export($f);');
	
	eval('$g = 60;');
	eval('$h = $g;');
	eval('fun(&$h);');
	eval('var_export($g);');
	eval('var_export($h);');
	eval('$h = \'y\';');
	eval('var_export($g);');
	eval('var_export($h);');

	eval('$i = 70;');
	eval('$j = $i;');
	eval('fun_r($j);');
	eval('var_export($i);');
	eval('var_export($j);');
	eval('$j = \'y\';');
	eval('var_export($i);');
	eval('var_export($j);');

	eval('$k = 80;');
	eval('$l = $k;');
	eval('fun_r(&$l);');
	eval('var_export($k);');
	eval('var_export($l);');
	eval('$l = \'y\';');
	eval('var_export($k);');
	eval('var_export($l);');
	
	eval('$i1 = 71;');
	eval('$j1 = $i1;');
	eval('fun_rr($j1);');
	eval('var_export($i1);');
	eval('var_export($j1);');
	eval('$j1 = \'y\';');
	eval('var_export($i1);');
	eval('var_export($j1);');

	eval('$k1 = 81;');
	eval('$l1 = $k1;');
	eval('fun_rr(&$l1);');
	eval('var_export($k1);');
	eval('var_export($l1);');
	eval('$l1 = \'y\';');
	eval('var_export($k1);');
	eval('var_export($l1);');
	
	eval('echo "\n";');

	// Same again, but the variable passed in is now part of a 
	// change-on-write set (references another variable). 
	// In this section, in all cases where a pass-by-reference is involved,
	// both variables should be changed.

	eval('$m = 90;');
	eval('$n =& $m;');
	eval('fun($n);');
	eval('var_export($m);');
	eval('var_export($n);');
	eval('$m = \'y\';');
	eval('var_export($m);');
	eval('var_export($n);');

	eval('$o = 100;');
	eval('$p =& $o;');
	eval('fun(&$p);');
	eval('var_export($o);');
	eval('var_export($p);');
	eval('$p = \'y\';');
	eval('var_export($o);');
	eval('var_export($p);');

	eval('$q = 110;');
	eval('$r =& $q;');
	eval('fun_r($r);');
	eval('var_export($q);');
	eval('var_export($r);');
	eval('$r = \'y\';');
	eval('var_export($q);');
	eval('var_export($r);');

	eval('$s = 120;');
	eval('$t =& $s;');
	eval('fun_r(&$t);');
	eval('var_export($s);');
	eval('var_export($t);');
	eval('$t = \'y\';');
	eval('var_export($s);');
	eval('var_export($t);');

	eval('$q1 = 111;');
	eval('$r1 =& $q1;');
	eval('fun_rr($r1);');
	eval('var_export($q1);');
	eval('var_export($r1);');
	eval('$r1 = \'y\';');
	eval('var_export($q1);');
	eval('var_export($r1);');

	eval('$s1 = 121;');
	eval('$t1 =& $s1;');
	eval('fun_rr(&$t1);');
	eval('var_export($s1);');
	eval('var_export($t1);');
	eval('$t1 = \'y\';');
	eval('var_export($s1);');
	eval('var_export($t1);');

	eval('echo "\n";');
?>
