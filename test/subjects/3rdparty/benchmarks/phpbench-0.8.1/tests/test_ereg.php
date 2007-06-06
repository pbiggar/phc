<?php

function test_ereg($base) {
    $strings = array
      ('blah@example.com',
       'blou@example.org',
       'bleh@example.net',
       'blip@in-addr.arpa');    
    $t = (int) round($base / 5);
    test_start(__FUNCTION__);

    $matches = array();
    do {
	foreach ($strings as $string) {
	    if (eregi('^[a-z0-9]+([_\\.-][a-z0-9]+)*' .
		      '@([a-z0-9]+([\.-][a-z0-9]{1,})+)*$',
		 $string, $matches) <= 0 ||
		empty($matches[2])) {
		test_regression(__FUNCTION__);
	    }			   
	}
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_ereg_enabled() {
    return TRUE;
}

?>
