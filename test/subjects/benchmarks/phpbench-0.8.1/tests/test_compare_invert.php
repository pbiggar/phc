<?php

function test_compare_invert($base) {
    $a = array(42);
    
    $t = $base;
    test_start(__FUNCTION__);
    do {
	if (!$a) {
	    test_regression(__FUNCTION__);
	}
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_compare_invert_enabled() {
    return TRUE;
}

?>
