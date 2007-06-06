<?php

function test_local_integer_assign($base) {
    $t = $base;
    test_start(__FUNCTION__);    
    do {
	$a = 6;
	$b = 9;
	$c = 42;
	$d = 69;
	$e = 4242;
	$f = 17;
	$g = 3200000;
	$h = -3200000;
	$i = $a;
	$j = $b;
	$k = $c;
	$l = $d;
	$m = $e;
	$n = $f;
	$o = $g;
	$p = $h;
    } while (--$t !== 0);
    if ($g + $h !== 0) {    
	test_regression(__FUNCTION__);
    }    
    return test_end(__FUNCTION__);
}

function test_local_integer_assign_enabled() {
    return TRUE;
}

?>
