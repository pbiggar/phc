<?php
/* The Great Computer Language Shootout
   http://shootout.alioth.debian.org/
   contributed by Isaac Gouy
       
   php -q matrix.php 600
	  --range 10,200,400,600
*/ 


set_time_limit(0);

$SIZE = 30;

function mkMatrix ($rows, $cols) {
    $count = 1;
    for ($i=0; $i<$rows; $i++) {
	for ($j=0; $j<$cols; $j++) {
	    $m[$i][$j] = $count++;
	}
    }
    return $m;
}


function mkZeroMatrix ($rows, $cols) {
    for ($i=0; $i<$rows; $i++) {
	for ($j=0; $j<$cols; $j++) {
	    $m[$i][$j] = 0;
	}
    }
    return $m;
}


function mmult ($rows, $cols, &$m1, &$m2, &$mm) {
    for ($i=0; $i<$rows; $i++) {
	for ($j=0; $j<$cols; $j++) {
	    $x = 0;
	    for ($k=0; $k<$cols; $k++) {
		$x += $m1[$i][$k] * $m2[$k][$j];
	    }
	    $mm[$i][$j] = $x;
	}
    }
    return $mm;
}


$n = ($argc == 2) ? $argv[1] : 1;

$m1 = mkMatrix($SIZE, $SIZE);
$m2 = mkMatrix($SIZE, $SIZE);
$mm = mkZeroMatrix($SIZE, $SIZE);

while ($n--) 
    mmult($SIZE, $SIZE, $m1, $m2, $mm);


print "{$mm[0][0]} {$mm[2][3]} {$mm[3][2]} {$mm[4][4]}\n"; 

?>
