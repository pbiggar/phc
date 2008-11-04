<?php

function test_mt_rand($base) {
    $t = $base;
    test_start(__FUNCTION__);
    do {
	if (mt_rand(1, 255) <= 0) {
	    test_regression(__FUNCTION__);
	}
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_mt_rand_enabled() {
    return TRUE;
}

?>
