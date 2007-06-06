<?php

function test_preg_match($base) {
    $strings = array
      ('Wesh wesh yo',
       'wesh this is a benchmark',
       'the PHP benchmarks',
       'Yeah weshhh');    
    $t = (int) round($base / 5);
    test_start(__FUNCTION__);

    $matches = array();
    do {
	foreach ($strings as $string) {
	    if (preg_match
		('/(y(eah|o)|th(e|is)|wesh(hh)?|benchmarks?|a|php|is)/i',
		 $string, $matches) <= 0 ||
		empty($matches[1])) {
		test_regression(__FUNCTION__);
	    }			   
	}
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_preg_match_enabled() {
    return TRUE;
}

?>
