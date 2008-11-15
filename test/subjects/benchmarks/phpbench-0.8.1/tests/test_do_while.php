<?php

function test_do_while($base) {
    $t = (int) round($base / 10);
    test_start(__FUNCTION__);
    do {
	$d = 1000;
	do {
	    $d--;
	} while ($d !== 0);
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_do_while_enabled() {
    return TRUE;
}

?>
