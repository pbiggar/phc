<?php
/*
 $Id: ackermann.php,v 1.1 2004/02/16 14:35:19 tim Exp $
 http://www.bagley.org/~doug/shootout/
 from Alexander Klimov
*/
function Ack($m, $n){
  if($m == 0) return $n+1;
  if($n == 0) return Ack($m-1, 1);
  return Ack($m - 1, Ack($m, ($n - 1)));
}
$n = ($argc == 2) ? $argv[1] : 7;
$r = Ack(3,$n);
print "Ack(3,$n): $r\n";
?>
