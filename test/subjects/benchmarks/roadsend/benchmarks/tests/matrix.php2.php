<?php
/*
 $Id: matrix.php2.php,v 1.2 2004/05/24 15:11:20 tim Exp $
 http://www.bagley.org/~doug/shootout/
*/

//set_time_limit(0);

$SIZE = 20;

function mkmatrix ($rows, $cols) {
    $count = 1;
    $mx = array();
    for ($i=0; $i<$rows; $i++) {
	$row = array();
	for ($j=0; $j<$cols; $j++) {
	    $row[$j] = $count++;
	}
	$mx[$i] = $row;
    }
    return($mx);
}

function mmult ($rows, $cols, $m1, $m2) {
    $m3 = array();
    for ($i=0; $i<$rows; $i++) {
	$row = array();
	for ($j=0; $j<$cols; $j++) {
	    $x = 0;
	    for ($k=0; $k<$cols; $k++) {
		$x += $m1[$i][$k] * $m2[$k][$j];
	    }
	    $row[$j] = $x;
	}
	$m3[$i] = $row;
    }
    return($m3);
}

$n = ($argc == 2) ? $argv[1] : 100;
$m1 = mkmatrix($SIZE, $SIZE);
$m2 = mkmatrix($SIZE, $SIZE);
while ($n--) {
    $mm = mmult($SIZE, $SIZE, $m1, $m2);
}
print "{$mm[0][0]} {$mm[2][3]} {$mm[3][2]} {$mm[4][4]}\n";
?>
