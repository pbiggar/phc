<?php

function test_compare_false($base) {
    $a = array(42);
    
    $t = $base;
    test_start(__FUNCTION__);
    do {
	if ($a === FALSE) {
	    test_regression(__FUNCTION__);
	}
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_compare_false_enabled() {
    return TRUE;
}

?>
