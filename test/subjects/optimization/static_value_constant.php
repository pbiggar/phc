<?php

  define("VAL", true);

  function dump_value($val=VAL) {
    var_dump($val);
  }

  dump_value(123);
  dump_value(); // should update $val with true

?>
