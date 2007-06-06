<?php

function test_sha1($base) {
    $t = $base;
    test_start(__FUNCTION__);
    do {
	if (sha1($t) == '') {
	    test_regression(__FUNCTION__);
	}
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_sha1_enabled() {
    return TRUE;
}

?>
