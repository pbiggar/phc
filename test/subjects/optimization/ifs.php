<?php

  // If simplification pass.
  // The negation operator "!" will be removed and
  // the branch successors will be switched.

  $x = $_ENV['x'];
  if (!is_numeric($x))
    echo $x;

?>
