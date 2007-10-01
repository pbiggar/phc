<?php

function strcat($n) {
  $str = "";
  while ($n-- > 0) {
    $str .= "hello\n";
  }
  $len = strlen($str);
  print "$len\n";
}

strcat (20);

?>
