<?php
/*
 $Id: random.php,v 1.2 2004/04/21 14:23:45 tim Exp $
 http://www.bagley.org/~doug/shootout/
 tweaked by tim
*/
define("IM", 139968);
define("IA", 3877);
define("IC", 29573);

$LAST = 42;
function gen_random ($max) {
    global $LAST;
    return( ($max * ($LAST = ($LAST * IA + IC) % IM)) / IM );
}

$N = 1000000;
while ($N--) {
    gen_random(100.0);
}

printf("%.9f\n", gen_random(100.0));
?>
