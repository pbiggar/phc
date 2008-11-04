From "Performance and Evaluation of Lisp Systems" by Richard Gabriel 
pg. 102

"STAK is a variant of TAK; it uses special binding to pass arguments
rather than the normal argument-passing mechanism."

<?php

function stak($x1, $y1, $z1) {
  global $x, $y, $z;

  $x = $x1;
  $y = $y1;
  $z = $z1;
  return stak_aux();
}


function stak_aux() {
  global $x, $y, $z;

  if ( !($y < $x)) {
    return $z;
  } else {
    //no LET :(
    $savedx = $x;
    $savedy = $y;
    $savedz = $z;
    $x = $savedx - 1;
    $newx = stak_aux();
    
    $x = $savedy - 1;
    $y = $savedz;
    $z = $savedx;
    $newy = stak_aux();

    $x = $savedz - 1;
    $y = $savedx;
    $z = $savedy;
    $newz = stak_aux();
    
    $x = $newx;
    $y = $newy;
    $z = $newz;
    return stak_aux();
  }
}

print "result: " . stak(18, 12, 6) . "\n";

?>
    
    


