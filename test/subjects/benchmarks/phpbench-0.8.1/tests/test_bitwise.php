<?php

function test_bitwise($base) {
    $t = $base;
    test_start(__FUNCTION__);
    do {
	$a = 0x7fffffff;
	$a = $a & 0xfefefefe;
	$a = $a | 0x07070707;
	$a = $a ^ 0xdeadbeef;
	$a = ~$a;
	$b = $a << 11;
	$c = $a >> 15;
    } while (--$t !== 0);

    if ("$a$b$c" !== '1588444911184493465648475' &&
	"$a$b$c" !== '-2706522385-5542957844480-82597') {
	test_regression(__FUNCTION__);
    }
    return test_end(__FUNCTION__);
}

function test_bitwise_enabled() {
    return TRUE;
}

?>
