<?php
/*
 $Id: hash.php,v 1.1 2004/02/16 14:35:19 tim Exp $
 http://www.bagley.org/~doug/shootout/
*/

$n = ($argc == 2) ? $argv[1] : 100000;

hash($n);

function hash($n) {

  for ($i = 1; $i <= $n; $i++) {
      $X[dechex($i)] = $i;
  }
  for ($i = $n; $i > 0; $i--) {
      if ($X[$i]) { $c++; }
  }
  print "$c\n";
}
?>
