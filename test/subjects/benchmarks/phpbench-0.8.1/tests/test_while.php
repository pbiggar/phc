<?php

function test_while($base) {
    $t = (int) round($base / 10);
    test_start(__FUNCTION__);
    do {
	$d = 1000;
	while ($d !== 0) {
	    $d--;
	}
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_while_enabled() {
    return TRUE;
}

?>
