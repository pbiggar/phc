<?php

function test_constants($base) {
    $t = $base;
    test_start(__FUNCTION__);
    define('TEST_CONSTANTS_XXX', 'xxx');
    define('TEST_CONSTANTS_NAME', 'TEST_CONSTANTS_XXX');
    do {
	$a = TEST_CONSTANTS_XXX;
	$b = defined(TEST_CONSTANTS_NAME);
	$c = constant(TEST_CONSTANTS_NAME);
    } while (--$t !== 0);

    if ("$a$b$c" !== 'xxx1xxx') {
	test_regression(__FUNCTION__);
    }
    return test_end(__FUNCTION__);
}

function test_constants_enabled() {
    return TRUE;
}

?>
