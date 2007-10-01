<?php

function mkmatrix ($rows, $cols) {
    $count = 1;
    $mx = array();
    for ($i=0; $i<$rows; $i++) {
	for ($j=0; $j<$cols; $j++) {
	    $mx[$i][$j] = $count++;
	}
    }
    return($mx);
}

function mmult ($rows, $cols, $m1, $m2) {
    $m3 = array();
    for ($i=0; $i<$rows; $i++) {
	for ($j=0; $j<$cols; $j++) {
	    $x = 0;
	    for ($k=0; $k<$cols; $k++) {
		$x += $m1[$i][$k] * $m2[$k][$j];
	    }
	    $m3[$i][$j] = $x;
	}
    }
    return($m3);
}



function matrix($n) {
  $SIZE = 10;
  $m1 = mkmatrix($SIZE, $SIZE);
  $m2 = mkmatrix($SIZE, $SIZE);
  while ($n--) {
    $mm = mmult($SIZE, $SIZE, $m1, $m2);
  }
  print "{$mm[0][0]} {$mm[2][3]} {$mm[3][2]} {$mm[4][4]}\n";
}

matrix (2);

?>
