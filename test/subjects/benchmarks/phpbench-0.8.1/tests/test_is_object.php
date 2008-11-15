<?php

function test_is_object($base) {
    $a = str_repeat('xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx', 1000);    
    
    $t = $base;
    test_start(__FUNCTION__);
    do {
	if (is_object($a)) {
	    test_regression(__FUNCTION__);
	}
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_is_object_enabled() {
    return TRUE;
}

?>
