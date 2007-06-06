<?php

function test_global_string_assign($base) {
    $t = $base;
    test_start(__FUNCTION__);    
    
    global $a, $b, $c, $d, $e, $f, $g, $h;
    global $i, $j, $k, $l, $m, $n, $o, $p;
    do {
	$a = 'abcdefghijklmnop';
	$b = $a;
	$c = $a . $b;
	$d = $c . $a;
	$e = $a . $c . $d . $b;
	$f = $a . $c;
	$g = $b . $d;
	$h = $a . $b . $c . $d . $e . $f . $g;
	$i = $a;
	$j = $b;
	$k = $c;
	$l = $d;
	$m = $e;
	$n = $f;
	$o = $g;
	$p = $h;
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_global_string_assign_enabled() {
    return TRUE;
}

?>
