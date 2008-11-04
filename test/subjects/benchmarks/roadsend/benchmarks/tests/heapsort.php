<?php
/*
 $Id: heapsort.php,v 1.2 2004/04/21 14:23:45 tim Exp $
 http://www.bagley.org/~doug/shootout/
*/
define("IM", 139968);
define("IA", 3877);
define("IC", 29573);

$LAST = 42;
function gen_random ($n) {
    global $LAST;
    return( ($n * ($LAST = ($LAST * IA + IC) % IM)) / IM );
}

function heapsort ($n, &$ra) {
    $l = ($n >> 1) + 1;
    $ir = $n;

    while (1) {
	if ($l > 1) {
	    $rra = $ra[--$l];
	} else {
	    $rra = $ra[$ir];
	    $ra[$ir] = $ra[1];
	    if (--$ir == 1) {
		$ra[1] = $rra;
		return;
	    }
	}
	$i = $l;
	$j = $l << 1;
	while ($j <= $ir) {
	    if (($j < $ir) && ($ra[$j] < $ra[$j+1])) {
		$j++;
	    }
	    if ($rra < $ra[$j]) {
		$ra[$i] = $ra[$j];
		$j += ($i = $j);
	    } else {
		$j = $ir + 1;
	    }
	}
	$ra[$i] = $rra;
    }
}


$N = ($argc == 2) ? $argv[1] : 10000;

for ($i=1; $i<=$N; $i++) {
    $ary[$i] = gen_random(1);
}

/*
for ($i=0; $i<$N; $i++) {
    printf("%4d %.15f\n", $i, $ary[$i]);
}
*/

heapsort($N, $ary);

printf("%.10f\n", $ary[$N]);
?>
