<?php

function test_local_float_assign($base) {
    $t = $base;
    test_start(__FUNCTION__);    
    do {
	$a = 6.42;
	$b = 9.42;
	$c = 42.42;
	$d = 69.42;
	$e = 4242.42;
	$f = 17.42;
	$g = 3200000.42;
	$h = -3200000.42;
	$i = $a;
	$j = $b;
	$k = $c;
	$l = $d;
	$m = $e;
	$n = $f;
	$o = $g;
	$p = $h;
    } while (--$t !== 0);
    if (!is_float($a) || $g + $h !== 0.0) {    
	test_regression(__FUNCTION__);
    }    
    return test_end(__FUNCTION__);
}

function test_local_float_assign_enabled() {
    return TRUE;
}

?>
