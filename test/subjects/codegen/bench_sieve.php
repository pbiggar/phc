<?php


function sieve($n) {
  $count = 0;
  while ($n-- > 0) {
    $count = 0;
    $flags = range (0,92);
    for ($i=2; $i<93; $i++) {
      if ($flags[$i] > 0) {
        for ($k=$i+$i; $k <= 92; $k+=$i) {
          $flags[$k] = 0;
        }
        $count++;
      }
    }
  }
  print "Count: $count\n";
}

sieve (3);

?>
