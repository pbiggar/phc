<?php

function test_foreach($base) {
    $a = array();
    $b = array();
    $c = array();
    $t = 100;
    do {
	$a['x' . $t] = $t . 'x';
	$t--;
    } while ($t !== 0);
    $t = 10;
    do {
	$b[$t . 'x'] = 'x' . $t;
	$t--;
    } while ($t !== 0);
    
    $t = (int) round($base / 15);
    test_start(__FUNCTION__);
    do {
	$d = 0;
	foreach ($a as $k => $v) {
	    foreach ($b as $k => $v) {
		$d++;
	    }
	}
	foreach ($c as $v) {
	    $d++;
	}
    } while (--$t !== 0);

    if ($d !== 1000) {
	test_regression(__FUNCTION__);
    }    
    return test_end(__FUNCTION__);
}

function test_foreach_enabled() {
    return TRUE;
}

?>
