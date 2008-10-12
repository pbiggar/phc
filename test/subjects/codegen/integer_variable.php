<?php
  $x = 5;
  $$x = "a";
  $y = $$x;
  echo "y is $y\n";
?>
