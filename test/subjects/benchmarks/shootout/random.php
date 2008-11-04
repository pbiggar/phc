<?php
/*
 $Id: random.php,v 1.3 2004-10-11 04:47:51 bfulgham Exp $
 http://shootout.alioth.debian.org/
	  --range 9000,300000,600000,900000 
*/
define("IM", 139968);
define("IA", 3877);
define("IC", 29573);

$LAST = 42;
function gen_random ($max) {
    global $LAST;
    return( ($max * ($LAST = ($LAST * IA + IC) % IM)) / IM );
}

$N = (($argc == 2) ? $argv[1] : 1) - 1;
while ($N--) {
    gen_random(100.0);
}

printf("%.9f\n", gen_random(100.0));
?>
