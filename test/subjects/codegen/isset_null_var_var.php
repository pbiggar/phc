<?php
  if(isset($$x)) echo "null var var is set\n"; else echo "null var var is not set\n";
  $GLOBALS[""] = 1;
  if(isset($$x)) echo "null var var is set\n"; else echo "null var var is not set\n";
  $GLOBALS[""] = NULL;
  if(isset($$x)) echo "null var var is set\n"; else echo "null var var is not set\n";
?>
