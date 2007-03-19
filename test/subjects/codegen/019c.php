<?php
	eval("\$a = 5;");
	eval("\$b[1] =& \$a;");
	eval("\$b[1] = 6;");
	var_dump(&$a);
	var_dump(&$b);
?>
