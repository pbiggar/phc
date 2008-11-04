<?php

function test_switch($base) {
    $t = $base;
    test_start(__FUNCTION__);    
    do {
	$a = 1;
	do {
	    switch ($a) {
	     case 1:
		$a = 2;
		break;
	     case 2:
		$a = 3;
		break;
	     case 3:
		$a = 4;
		break;
	     case 4:
		$a = 'five';
		break;
	     case 'five':
		$a = 'six';
		break;
	     case 'six':
		$a = 'seven';
		break;
	     case 'seven':
		$a = 'height';
		break;
	     case 'height':
		$a = 9;
		break;
	     case 'not_reached':
	     case 42:
		continue;
	     default:
		$a = 'end';		
	    }
	} while ($a !== 'end');
    } while (--$t !== 0);

    return test_end(__FUNCTION__);
}

function test_switch_enabled() {
    return TRUE;
}

?>
