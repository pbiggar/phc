<?php
	eval(<<<PHP
	class C
	{
		function __set(\$var, \$value)
		{
			echo("__set(\$var, \$value)\n");
			\$this->\$var = \$value;
		}
	}

	\$c = new C();
PHP
	);

	$c->a = 1;
	$c->a = 2;
	$c->b = 3;
	var_dump($c);
?>
