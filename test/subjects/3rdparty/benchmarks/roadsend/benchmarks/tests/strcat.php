<?php
/*
 $Id: strcat.php,v 1.4 2004/04/21 14:23:45 tim Exp $
 http://www.bagley.org/~doug/shootout/
*/
$n = ($argc == 2) ? $argv[1] : 10000;

mystrcat($n);

function mystrcat($n) {
  $str = "";
  while ($n-- > 0) {
    $str .= "hello\n";
    $str = $str . "goodbye" . "hello\n";
  }
  $len = strlen($str);
  print "$len\n";
}

?>


<?

$a[] = 'zot';
$a[] = 'zotzot';
$a[] = 'zotzotzot';
$a[] = 'zotzotzotzot';
$a[] = 'zotzotzotzotzot';
$a[] = 'zotzotzotzotzotzot';
$a[] = 'zotzotzotzotzotzotzot';
$a[] = 'zotzotzotzotzotzotzotzot';
$a[] = 'zotzotzotzotzotzotzotzotzot';

function afunc() {
    global $a;
    $b = NULL;
    for ($i=0; $i<1000; $i++) {
        foreach ($a as $val) {
            $b .= $val;
        }
    }
    
    echo $b;
}

afunc();


?>

