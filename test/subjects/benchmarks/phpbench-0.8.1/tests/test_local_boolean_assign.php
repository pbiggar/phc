<?php

function test_local_boolean_assign($base) {
    $t = $base;
    test_start(__FUNCTION__);    
    do {
	$a = TRUE;
	$b = FALSE;
	$c = TRUE;
	$d = FALSE;
	$e = TRUE;
	$f = FALSE;
	$g = TRUE;
	$h = FALSE;
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

function test_local_boolean_assign_enabled() {
    return TRUE;
}

?>
