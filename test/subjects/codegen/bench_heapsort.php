<?php

function gen_random ($n) {
    global $LAST;
    return( ($n * ($LAST = ($LAST * IA + IC) % IM)) / IM );
}

function heapsort_r($n, &$ra) {
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

function heapsort($N) {
  global $LAST;

  define("IM", 139968);
  define("IA", 3877);
  define("IC", 29573);

  $LAST = 42;
  for ($i=1; $i<=$N; $i++) {
    $ary[$i] = gen_random(1);
  }
  heapsort_r($N, $ary);
  printf("%.10f\n", $ary[$N]);
}

heapsort (7);

?>
