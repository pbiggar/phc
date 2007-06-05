<?php
/*
 $Id: nestedloop.php,v 1.1 2004/02/16 14:35:19 tim Exp $
 http://www.bagley.org/~doug/shootout/
*/
$n = ($argc == 2) ? $argv[1] : 100;
nestedloop($n);
function nestedloop($n) {
$x = 0;
for ($a=0; $a<$n; $a++)
  for ($b=0; $b<$n; $b++)
    for ($f=0; $f<$n; $f++)
      $x++;
print "$x\n";
}

?>
