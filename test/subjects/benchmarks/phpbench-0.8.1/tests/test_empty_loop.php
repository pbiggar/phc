<?php

function test_empty_loop($base) {
    $t = $base * 30;
    test_start(__FUNCTION__);
    do {

    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_empty_loop_enabled() {
    return TRUE;
}

?>
