<?php

function test_chr_var($base) {
    $t = (int) round($base / 10);
    test_start(__FUNCTION__);
    do {
	$b = '';
	$c = 256;
	do {
	    $c--;
	    $b .= chr($c);
	} while ($c !== 0);
    } while (--$t !== 0);

    if (md5($b) !== 'ec6df70f2569891eae50321a9179eb82') {	
	test_regression(__FUNCTION__);
    }    
    return test_end(__FUNCTION__);
}

function test_chr_var_enabled() {
    return TRUE;
}

?>
