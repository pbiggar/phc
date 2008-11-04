<?php

function test_strlen($base) {
    $a = str_repeat('xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx', 1000);    
    
    $t = $base;
    test_start(__FUNCTION__);
    do {
	if (strlen($a) !== 42000) {
	    test_regression(__FUNCTION__);
	}
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_strlen_enabled() {
    return TRUE;
}

?>
