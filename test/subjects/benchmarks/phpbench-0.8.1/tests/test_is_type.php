<?php

function test_is_type($base) {
    $a = 1;
    $b = 'Yeepee !';
    $c = TRUE;
    $d = 3.141592653;
      
    $t = $base;
    test_start(__FUNCTION__);    
    do {	
	if (is_string($a) || is_bool($b) || is_float($c) || is_int($d)) {
	    die();
	}
    } while (--$t !== 0);

    if (!(is_int($a) && is_string($b) && is_bool($c) && is_float($d))) {
	test_regression(__FUNCTION__);
    }    
    return test_end(__FUNCTION__);
}

function test_is_type_enabled() {
    return TRUE;
}

?>
