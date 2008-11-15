an effort to make a more clear globals benchmark
<?php

while ($aglobal < 1000000) {
	$aglobal++;
	$j = $aglobal;
	$another = $j;
	$another1 = $j;
	$another2 = $j;
	$another3 = $j;
}

print "aglobal $aglobal, j $j, another $another\n";
?>