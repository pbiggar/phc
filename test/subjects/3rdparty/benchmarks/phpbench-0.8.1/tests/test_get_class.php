<?php

class TestGetClass {
    function TestGetClass() {
	return;
    }
    function ok() {
	return TRUE;
    }
};

function test_get_class($base) {
    $a = new TestGetClass();
    
    $t = $base;
    test_start(__FUNCTION__);
    do {
	if (strtolower(get_class($a)) !== 'testgetclass') {
	    test_regression(__FUNCTION__);
	}
    } while (--$t !== 0);

    if (!is_object($a) || $a->ok() !== TRUE) {
	test_regression(__FUNCTION__);
    }    
    return test_end(__FUNCTION__);
}

function test_get_class_enabled() {
    return TRUE;
}

?>
