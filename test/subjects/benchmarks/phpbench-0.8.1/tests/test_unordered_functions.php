<?php

function test_unordered_functions($base) {
    $t = $base;
    test_start(__FUNCTION__);
    do {
	$a = tuf_1(42, -1);
	$b = tuf_1($a, 42.67);
	$c = tuf_1($b, 'xxx');
	$d = tuf_1($c, NULL);
	$e = tuf_1($a, tuf_1($b, tuf_1($c, tuf_1($d, $a))));
    } while (--$t !== 0);

    if ("$a$b$c$d$e" !== '4183.6783.6783.67333.01') {
	test_regression(__FUNCTION__);
    }
    return test_end(__FUNCTION__);
}

function tuf_1($a, $b) {
    return tuf_2($a, $b);
}

function tuf_2($a, $b) {
    return tuf_3($a, $b);
}

function tuf_3($a, $b) {
    return tuf_4($a, $b);
}

function tuf_4($a, $b) {
    return tuf_5($a, $b);
}

function tuf_5($a, $b) {
    return $a + $b;
}

function test_unordered_functions_enabled() {
    return TRUE;
}

?>
