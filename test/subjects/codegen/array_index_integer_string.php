<?php
  // Indexing an array with a string-that-is-an-integer should be an
  // integer indexing operation, *not* a string operation
  // In other words, this program should not output anything:
  $x = 5;
  $$x = "a";
  echo $GLOBALS["5"];
?>
