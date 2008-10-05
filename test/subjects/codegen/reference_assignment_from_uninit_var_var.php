<?php
	$x = "a";
	$b =& $$x;
  $b = 1;
  echo $a;
?>
