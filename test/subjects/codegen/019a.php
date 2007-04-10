<?php
	eval("\$a = 5;");
	eval("\$b[1] =& \$a;");
	eval("\$b[1] = 6;");
	eval("var_dump(\$a);");
	eval("var_dump(\$b);");
?>
