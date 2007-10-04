<?php
	if(isset($a, $b)) echo "1\n";

	$c = 1;
	if(isset($c, $d)) echo "2\n";

	$f = 2;
	if(isset($e, $f)) echo "3\n";

	$g = 3;
	$h = 4;
	if(isset($g, $h)) echo "4\n";

	if(isset($c, $g, $h)) echo "5\n";
	if(isset($d, $g, $h)) echo "6\n";
?>
