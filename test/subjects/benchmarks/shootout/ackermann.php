<?php
/*
 $Id: ackermann.php,v 1.2 2004-10-11 04:47:17 bfulgham Exp $
 http://www.bagley.org/~doug/shootout/
 from Alexander Klimov


RUNTESTS := --range 9,10,11
*/
function Ack($m, $n){
  if($m == 0) return $n+1;
  if($n == 0) return Ack($m-1, 1);
  return Ack($m - 1, Ack($m, ($n - 1)));
}
$n = ($argc == 2) ? $argv[1] : 1;
$r = Ack(3,$n);
print "Ack(3,$n): $r\n";
?>
