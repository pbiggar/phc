<?php
/*
 $Id: ary2.php,v 1.1 2004/02/16 14:35:19 tim Exp $
 http://www.bagley.org/~doug/shootout/
*/
$n = ($argc == 2) ? $argv[1] : 100000;

ary2($n);

function ary2($n) {
  for ($i=0; $i<$n;) {
      $X[$i] = $i; ++$i;
      $X[$i] = $i; ++$i;
      $X[$i] = $i; ++$i;
      $X[$i] = $i; ++$i;
      $X[$i] = $i; ++$i;
  
      $X[$i] = $i; ++$i;
      $X[$i] = $i; ++$i;
      $X[$i] = $i; ++$i;
      $X[$i] = $i; ++$i;
      $X[$i] = $i; ++$i;
  }
  for ($i=$n-1; $i>=0; $i--) {
      $Y[$i] = $X[$i]; --$i;
      $Y[$i] = $X[$i]; --$i;
      $Y[$i] = $X[$i]; --$i;
      $Y[$i] = $X[$i]; --$i;
      $Y[$i] = $X[$i]; --$i;
  
      $Y[$i] = $X[$i]; --$i;
      $Y[$i] = $X[$i]; --$i;
      $Y[$i] = $X[$i]; --$i;
      $Y[$i] = $X[$i]; --$i;
      $Y[$i] = $X[$i]; --$i;
  }
  $last = $n-1;
  print "$Y[$last]\n";
}


?>
