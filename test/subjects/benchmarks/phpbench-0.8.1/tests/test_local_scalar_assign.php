<?php

function test_local_scalar_assign($base) {
    $t = $base;
    test_start(__FUNCTION__);    
    do {
	$a = 1;
	$b = $a;
	$c = $a + $b;
	$d = $c - $a;
	$e = $a + $c - $d - $b;
	$f = $a | $c;
	$g = $b & $d;
	$h = $a ^ $b ^ $c ^ $d ^ $e ^ $f ^ $g;
	$i = $a;
	$j = $b;
	$k = $c;
	$l = $d;
	$m = $e;
	$n = $f;
	$o = $g;
	$p = $h;
    } while (--$t !== 0);
    if (md5($a . $b . $c . $d . $e . $f . $g . $h .
	    $i . $j . $k . $l . $m . $n . $o . $p)
	!== 'efe1603e8bbb8403b6bfe7a43a39ade1') {
	test_regression(__FUNCTION__);
    }
    return test_end(__FUNCTION__);
}

function test_local_scalar_assign_enabled() {
    return TRUE;
}

?>
