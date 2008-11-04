<?php

function test_ord($base) {
    $a = str_repeat('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOP', 10);
    $a_len = strlen($a);
    
    $t = (int) round($base / 10);
    test_start(__FUNCTION__);
    do {
	$b = 0;	
	$c = $a_len;	
	do {
	    $c--;
	    $b += ord($a[$c]);
	    $b += ord('A') - 65;
	    $b += ord('0') - 48;
	} while ($c !== 0);
    } while (--$t !== 0);

    if ($b !== 40070) {
	test_regression(__FUNCTION__);
    }    
    return test_end(__FUNCTION__);
}

function test_ord_enabled() {
    return TRUE;
}

?>
