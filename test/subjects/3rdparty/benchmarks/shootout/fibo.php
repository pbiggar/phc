<?php
/*
 $Id: fibo.php,v 1.4 2005-04-25 19:01:38 igouy-guest Exp $
 http://shootout.alioth.debian.org/
*/

/* --range 12,24,32  */
function fibo($n){
    return(($n < 2) ? 1 : fibo($n - 2) + fibo($n - 1));
}
$n = ($argc == 2) ? $argv[1] : 1;
$r = fibo($n);
print "$r\n";
?>
