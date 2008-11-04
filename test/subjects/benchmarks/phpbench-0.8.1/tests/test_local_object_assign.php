<?php

class TestLocalObjectAssign {
    function TestLocalObjectAssign() {
	return;
    }
    function ok() {
	return TRUE;
    }
};

function test_local_object_assign($base) {
    $t = $base;
    test_start(__FUNCTION__);
    do {
	$a = new TestLocalObjectAssign();
    } while (--$t !== 0);

    if (!is_object($a) || $a->ok() !== TRUE) {
	test_regression(__FUNCTION__);
    }    
    return test_end(__FUNCTION__);
}

function test_local_object_assign_enabled() {
    return TRUE;
}

?>
