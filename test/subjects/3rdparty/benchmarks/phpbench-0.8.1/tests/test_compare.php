<?php

function test_compare($base) {
    $a = 42;
    $b = '69';
    
    $t = $base;
    test_start(__FUNCTION__);
    do {
	$c = ($a == $b);
	$d = ($a === $b);
	$e = ($a != $b);	
	$f = ($a !== $b);
	$g = ($a < $b);	
	$h = ($a > $b);
	$i = ($a <= $b);
	$j = ($a >= $b);
    } while (--$t !== 0);

    if ("$c $d $e $f $g $h $i $j" !== '  1 1 1  1 ') {
	test_regression(__FUNCTION__);
    }
    return test_end(__FUNCTION__);
}

function test_compare_enabled() {
    return TRUE;
}

?>
