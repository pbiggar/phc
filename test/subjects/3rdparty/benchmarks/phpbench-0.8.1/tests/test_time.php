<?php

function test_time($base) {
    $t = $base;
    test_start(__FUNCTION__);
    do {
	$a = time();
	if (time() < $a) {
	    test_regression(__FUNCTION__);
	}
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_time_enabled() {
    return TRUE;
}

?>
