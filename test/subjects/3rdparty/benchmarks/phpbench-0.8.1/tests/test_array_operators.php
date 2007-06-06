<?php

function test_array_operators($base) {
    $a = array(42, 64, 99);
    $b = array('42', '64', '99');	
    $c = array('x42', 'x64', 'x99');
    
    $t = $base;
    test_start(__FUNCTION__);
    do {
	$d = $a + $b + $c;
	$e = ($a == $b);
	$f = ($a === $b);
	$g = ($a <> $b);
	$h = ($a !== $b);
    } while (--$t !== 0);

    if (count($a) . count($b) . count($c) . count($d) .
	$e . $f . $g . $h !== '333311') {
	test_regression(__FUNCTION__);
    }
    return test_end(__FUNCTION__);
}

function test_array_operators_enabled() {
    return TRUE;
}

?>
