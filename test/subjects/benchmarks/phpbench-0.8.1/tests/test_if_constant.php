<?php

function test_if_constant($base) {
    $t = $base;
    test_start(__FUNCTION__);    
    do {
	if (FALSE) {
	    test_regression(__FUNCTION__);
	}
	if (0) {
	    test_regression(__FUNCTION__);
	}
	if (42 === 69) {
	    test_regression(__FUNCTION__);
	} elseif (6 * 9 === 42) {
	    test_regression(__FUNCTION__);	    
	}
	if (69 !== 42) {
	    
	} else {
	    test_regression(__FUNCTION__);	    
	}
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_if_constant_enabled() {
    return TRUE;
}

?>
