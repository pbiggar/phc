<?php

	// Taken from the Zend benchmark. Shredding should take care of the compound assignment
define("IM", 139968);
define("IA", 3877);
define("IC", 29573);

$LAST = 42;
 
function gen_random ($n) {
    global $LAST;
    return( ($n * ($LAST = ($LAST * IA + IC) % IM)) / IM );
}

for ($i = 0; $i < 20; $i++)
{
	$x = gen_random ($i);
	echo "$x\n";
}

?>
