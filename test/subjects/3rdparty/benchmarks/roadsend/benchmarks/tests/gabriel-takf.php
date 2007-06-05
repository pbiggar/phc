From "Performance and Evaluation of Lisp Systems" by Richard Gabriel 
pg. 100

"TAKF is an alternative TAK formulation proposed by George Carrette,
who was working on the Vax NIL project at MIT when the benchmark study
was started."

<?php

function takf($x, $y, $z) {
  return takfsub("takfsub", $x, $y, $z);
}

function takfsub($f, $x, $y, $z) {
  if ( !($y < $x) ) {
    return $z;
  } else {
    return $f($f, $f($f, $x - 1, $y, $z),
	      $f($f, $y - 1, $z, $x),
	      $f($f, $z - 1, $x, $y));
  }
}

print "result: " . takf(18, 12, 6) . "\n";
      

?>
