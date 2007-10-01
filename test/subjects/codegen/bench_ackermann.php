<?php

function Ack($m, $n){
  if($m == 0) return $n+1;
  if($n == 0) return Ack($m-1, 1);
  return Ack($m - 1, Ack($m, ($n - 1)));
}

function ackermann($n) {
  $r = Ack(3,$n);
  print "Ack(3,$n): $r\n";
}

ackermann (3);

?>
