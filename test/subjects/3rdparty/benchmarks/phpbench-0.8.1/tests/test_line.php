<?php

function test_line($base) {
    $t = $base;
    test_start(__FUNCTION__);
    $a = 0;
    do {
	$a += __LINE__;
	$a -= __LINE__;
	$a++;
    } while (--$t !== 0);

    if ($a !== 0) {
	test_regression(__FUNCTION__);
    }
    return test_end(__FUNCTION__);
}

function test_line_enabled() {
    return TRUE;
}

?>
