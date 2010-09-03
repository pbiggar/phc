<?php
 // The $x[0] is not supposed to be killed by dce. Fixed now.
 $x = array();
 $x[0] = rand();
 $y[0] = "anything";
 echo $x[0];
?>
