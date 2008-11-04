<?php

function test_empty($base) {
    $a = str_repeat('xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx', 1000);    
    
    $t = $base;
    test_start(__FUNCTION__);
    do {
	if (empty($a)) {
	    test_regression(__FUNCTION__);
	}
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_empty_enabled() {
    return TRUE;
}

?>
