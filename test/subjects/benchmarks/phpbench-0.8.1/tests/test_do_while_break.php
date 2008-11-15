<?php

function test_do_while_break($base) {
    $t = $base * 10;
    test_start(__FUNCTION__);
    do {
	$d = 1000;
	do {
	    break;
	} while ($d !== 0);
	for (;;) {
	    break;
	}
    } while (--$t !== 0);

    if ($d !== 1000) {
	test_regression(__FUNCTION__);
    }
    return test_end(__FUNCTION__);
}

function test_do_while_break_enabled() {
    return TRUE;
}

?>
