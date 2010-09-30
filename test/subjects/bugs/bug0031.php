<?php

  //Bug report from Kevin Day
  //die does not work

  die;
  echo "'die' ignored\n";
  die();
  echo "'die()' ignored\n";
  die(1);
  echo "'die(1)' ignored\n"

?>
