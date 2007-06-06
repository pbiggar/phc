<?php

function test_references($base) {
    $t = $base;
    test_start(__FUNCTION__);
    do {
	$a = 42;
	$b = &$a;
	$b = 69;
	$c = &$b;
	$a = 17;
	$c = 21;
    } while (--$t !== 0);

    if ("$a$b$c" !== '212121') {
	test_regression(__FUNCTION__);
    }
    return test_end(__FUNCTION__);
}

function test_references_enabled() {
    return TRUE;
}

?>
