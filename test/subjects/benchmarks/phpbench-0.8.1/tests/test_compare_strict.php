<?php

function test_compare_strict($base) {
    $a = 42;
    $b = '69';
    
    $t = $base;
    test_start(__FUNCTION__);
    do {
	$c = ($a === $b);
	$d = ($a !== $b);
    } while (--$t !== 0);

    if ("$c $d" !== ' 1') {
	test_regression(__FUNCTION__);
    }
    return test_end(__FUNCTION__);
}

function test_compare_strict_enabled() {
    return TRUE;
}

?>
