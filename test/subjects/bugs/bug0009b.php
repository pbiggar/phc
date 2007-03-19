<?php
	// This bug is particularly important together with bug0009
	// In particular, the DOT file corresponding to this PHP file should
	// not include _any_ unary operators.
	echo 1 + 1;
	echo 1+ 1;
	echo 1 +1;
	echo 1+1;
	echo +1 + +1;
	echo +1+ +1;
	
	echo 1 - 1;
	echo 1- 1;
	echo 1 -1;
	echo 1-1;
	echo -1 - -1;
	echo -1- -1;
	echo -1- - - - - 6;
?>
