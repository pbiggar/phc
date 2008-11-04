<?php

function test_string_append($base) {
    $t = $base;
    test_start(__FUNCTION__);
    do {
	$a = 'abc';
	$b = 'def';
	$a .= $b;
	$b .= $a . $b . $a . $b;
	$a = "$a $b $b $a";
	$a .= 'x' . 'y' . 'z';
	$b .= "$a$b" . 'hij';
    } while (--$t !== 0);

    if (md5("$a$b") !== 'b7988e4fb634f7e856fb19d7005d9dfa') {
	test_regression(__FUNCTION__);
    }
    return test_end(__FUNCTION__);
}

function test_string_append_enabled() {
    return TRUE;
}

?>
