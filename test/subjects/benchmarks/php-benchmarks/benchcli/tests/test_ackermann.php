<?php
/*
 $Id: test_ackermann.php,v 1.1 2009/05/24 19:01:24 hjalle Exp $
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
?>
