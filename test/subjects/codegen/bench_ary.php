<?php

function ary($n) {
  for ($i=0; $i<$n; $i++) {
    $X[$i] = $i;
  }
  for ($i=$n-1; $i>=0; $i--) {
    $Y[$i] = $X[$i];
  }
  $last = $n-1;
  print "$Y[$last]\n";
}


ary (5);

?>
