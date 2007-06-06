<?php

function test_local_hash_assign($base) {
    $a = array();    
    
    $t = $base;
    test_start(__FUNCTION__);
    do {
	$a['xxx'] = 'xxx';
	$a['1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25'] = $a['xxx'];
	$a['a, b'] = $a['1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25'];
	$a['yyy'] = $a['a, b'];
	$a[4242] = $a['yyy']; 
    } while (--$t !== 0);

    if (count($a) !== 5) {
	test_regression(__FUNCTION__);
    }    
    return test_end(__FUNCTION__);
}

function test_local_hash_assign_enabled() {
    return TRUE;
}

?>
