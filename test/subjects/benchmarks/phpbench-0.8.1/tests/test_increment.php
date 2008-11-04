<?php

function test_increment($base) {
    $t = $base;
    test_start(__FUNCTION__);
    do {
	$b = $a = 5;
	$c = $a++;
	$e = $d = ++$b;
	$f = ceil($d++);
	$g = floor(++$e);
	$h = $g += 2;
    } while (--$t !== 0);

    if ("$a$b$c$d$e$f$g$h" !== '66577699') {
	test_regression(__FUNCTION__);
    }
    return test_end(__FUNCTION__);
}

function test_increment_enabled() {
    return TRUE;
}

?>
