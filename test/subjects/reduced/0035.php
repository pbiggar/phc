<?php
	$x[5] = "a";
	$a = "foo\n";

	echo ${$x[5]};
	echo $$x[5];
?>
