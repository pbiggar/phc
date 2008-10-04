<?php
  function f()
  {
    $x = "a";
    global $$x;
    $a = 1;
  }

  f();
  echo $a;
?>
