<?php

function tof_5($a, $b) {
    return $a + $b;
}

function tof_4($a, $b) {
    return tof_5($a, $b);
}

function tof_3($a, $b) {
    return tof_4($a, $b);
}

function tof_2($a, $b) {
    return tof_3($a, $b);
}

function tof_1($a, $b) {
    return tof_2($a, $b);
}

function test_ordered_functions($base) {
    $t = $base;
    test_start(__FUNCTION__);
    do {
	$a = tof_1(42, -1);
	$b = tof_1($a, 42.67);
	$c = tof_1($b, 'xxx');
	$d = tof_1($c, NULL);
	$e = tof_1($a, tof_1($b, tof_1($c, tof_1($d, $a))));
    } while (--$t !== 0);

    if ("$a$b$c$d$e" !== '4183.6783.6783.67333.01') {
	test_regression(__FUNCTION__);
    }
    return test_end(__FUNCTION__);
}

function test_ordered_functions_enabled() {
    return TRUE;
}

?>
