<?php
/*
 * Test of function calls
 *
 * We define two functions fun and fun_r, both of which take a single argument
 * $x; but fun_r is compile-time-by-reference and fun is not.
 *
 * Tests are designed to check copy-on-write etc. stuff
 */

	function fun($x) { $x = 'x'; }
	function fun_r(&$x) { $x = 'x'; }

	// Test proper calling conventions in simple cases

	$a = 10;
	fun($a);
	var_export($a);

	$b = 20;
	fun(&$b);
	var_export($b);

	$c = 30;
	fun_r($c);
	var_export($c);

	$d = 40;
	fun_r(&$d);
	var_export($d);

	echo "\n";

	// Same as before, but the variable now passed in is part of a
	// copy-on-write set. In all cases where a pass-by-reference is involved,
	// only one of the two variables should be changed.

	$e = 50;
	$f = $e;
	fun($f);
	var_export($e);
	var_export($f);
	$f = 'y';
	var_export($e);
	var_export($f);
	
	$g = 60;
	$h = $g;
	fun(&$h);
	var_export($g);
	var_export($h);
	$h = 'y';
	var_export($g);
	var_export($h);

	$i = 70;
	$j = $i;
	fun_r($j);
	var_export($i);
	var_export($j);
	$j = 'y';
	var_export($i);
	var_export($j);

	$k = 80;
	$l = $k;
	fun_r(&$l);
	var_export($k);
	var_export($l);
	$l = 'y';
	var_export($k);
	var_export($l);
	
	echo "\n";

	// Same again, but the variable passed in is now part of a 
	// change-on-write set (references another variable). 
	// In this section, in all cases where a pass-by-reference is involved,
	// both variables should be changed.

	$m = 90;
	$n =& $m;
	fun($n);
	var_export($m);
	var_export($n);
	$m = 'y';
	var_export($m);
	var_export($n);

	$o = 100;
	$p =& $o;
	fun(&$p);
	var_export($o);
	var_export($p);
	$p = 'y';
	var_export($o);
	var_export($p);

	$q = 110;
	$r =& $q;
	fun_r($r);
	var_export($q);
	var_export($r);
	$r = 'y';
	var_export($q);
	var_export($r);

	$s = 120;
	$t =& $s;
	fun_r(&$t);
	var_export($s);
	var_export($t);
	$t = 'y';
	var_export($s);
	var_export($t);

	echo "\n";
?>
