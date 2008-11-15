<?php

function test_md5($base) {
    $t = $base;
    test_start(__FUNCTION__);
    do {
	if (md5($t) == '') {
	    test_regression(__FUNCTION__);
	}
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_md5_enabled() {
    return TRUE;
}

?>
