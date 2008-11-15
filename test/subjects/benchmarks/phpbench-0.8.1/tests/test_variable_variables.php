<?php

function test_variable_variables($base) {
    $t = $base;
    test_start(__FUNCTION__);
    do {
	$a = 'b';
	$$a = 'c';
	$$b = 'd';
	$$c = 'e';
	$$d = ${$c};
	$$$d = "$$b";
    } while (--$t !== 0);

    if ("$a$b$c$d$e" !== 'bcde$c') {
	test_regression(__FUNCTION__);
    }
    return test_end(__FUNCTION__);
}

function test_variable_variables_enabled() {
    return TRUE;
}

?>
