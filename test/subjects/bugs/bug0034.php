<?php

  // Issue 127 on bug reports.
  // This has been fixed by revision 3352.

  // The bug has happened because instruction (2) was failing to record
  // the use on the affected variable ($i). Because of that, the definition
  // on instruction (1) was having no uses, hence being killed on DCE pass.

  $i = $_ENV['i']; // (1)
  $i++;            // (2)
  echo $i;         // (3)

?>
