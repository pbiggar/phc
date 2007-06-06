<?php

function test_local_array_assign($base) {
    $t = $base;
    test_start(__FUNCTION__);    
    do {
	$a = array();
	$b = array(1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25);
	$c = array($a, $b);
	$d = array($b, $a);
	$e = array($c, $d);
	$f = array($a, $b, $c, $d, $e);
	$g = array(1, $a, 3, $b, 5, $c, 7, $d, 9, $e, 11, $f);
	$h = array($a, $b, $c, $d, $e, $f, $g);
    } while (--$t !== 0);
    
    if (count($h) !== 7) {
	test_regression(__FUNCTION__);
    }    
    return test_end(__FUNCTION__);
}

function test_local_array_assign_enabled() {
    return TRUE;
}

?>
