<?php
  $x = "a";
  $$x =& $b;
  $a = 1;
  echo $b; 
?>
