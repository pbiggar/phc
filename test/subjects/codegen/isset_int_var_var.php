<?php
  // Recall that variable names are *always* strings but array indices are integers *whenever possible*
  $x = 1;
  if(isset($$x)) echo "int var var is set\n"; else echo "int var var is not set\n";
  $GLOBALS[1] = "a"; 
  if(isset($$x)) echo "int var var is set\n"; else echo "int var var is not set\n";
  $GLOBALS["1"] = "b";
  if(isset($$x)) echo "int var var is set\n"; else echo "int var var is not set\n";
  ${1} = "c";
  if(isset($$x)) echo "int var var is set\n"; else echo "int var var is not set\n";
?>
