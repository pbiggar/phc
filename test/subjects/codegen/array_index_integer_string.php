<?php
  // Variable names should *always* be strings
  // Hence, this will *set* index "5" (even though the code says 5) 
  // but *read* index 5 (even though the code says "5") 
  // The output of the program is therefore blank.
  $x = 5;
  $$x = "a";
  echo $GLOBALS["5"];
?>
