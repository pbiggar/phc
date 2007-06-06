<?php

function test_arithmetic($base) {
    $t = $base;
    test_start(__FUNCTION__);
    do {
	$a = 5;
	$b = - $a;
	$a = $a + $b;
	$b = $a - $b;
	$a = $a * $b;
	$c = $a;
	$a = 1; // avoid divide by zero warning
	@$b = $b / $a;
	$a = $a % $b;
    } while (--$t !== 0);

    if (!(empty($a) && empty($b)) || $c !== 0) {
//	test_regression(__FUNCTION__);
    }
    return test_end(__FUNCTION__);
}

function test_arithmetic_enabled() {
    return TRUE;
}

?>
