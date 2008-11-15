<?php

function test_microtime($base) {
    $t = $base;
    test_start(__FUNCTION__);
    do {
	$a = microtime();
	$b = microtime();
	if ($a[0] < $b[0]) {
	    test_regression(__FUNCTION__);
	}
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_microtime_enabled() {
    return TRUE;
}

?>
