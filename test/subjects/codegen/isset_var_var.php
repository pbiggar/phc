<?php
  $a = 1;
  $x = "a";
  $y = "b";
  if(isset($$x)) echo "a is set\n"; else echo "a is not set\n";
  if(isset($$y)) echo "b is set\n"; else echo "b is not set\n";
?>
