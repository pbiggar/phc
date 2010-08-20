<?php

  $x = $_ENV['x'];
  $y = & $x;

  if ($x > 0)
    echo $y;

?>
