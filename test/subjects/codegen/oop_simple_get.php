<?php
	eval(<<<PHP
	class C
	{
		function __get(\$var)
		{
			echo("__get(\$var)\n");
			return 1; 
		}
	}

	\$c = new C();
PHP
	);

	var_dump($c->a);
	$c->a = 2;
	var_dump($c->a);
?>
