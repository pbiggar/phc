<?php

function test_crc32($base) {
    $t = $base;
    test_start(__FUNCTION__);
    do {
	if (crc32($t) == '') {
	    test_regression(__FUNCTION__);
	}
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_crc32_enabled() {
    return TRUE;
}

?>
