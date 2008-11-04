<?php

function test_chr_fixed($base) {
    $t = (int) round($base / 10);
    test_start(__FUNCTION__);
    do {
	$b = '';
	$c = 256;
	do {
	    $c--;
	    $b .= chr(128);
	} while ($c !== 0);
    } while (--$t !== 0);
    
    if (md5($b) !== 'b031e074f57a105f0d91cca34e902c82') {	
	test_regression(__FUNCTION__);
    }    
    return test_end(__FUNCTION__);
}

function test_chr_fixed_enabled() {
    return TRUE;
}

?>
