<?php

	class A { static $q; var $z; }

	var_dump (A::$q++);
	var_dump (A::$q++);

	var_dump ($s++);
	var_dump ($s++);

	var_dump ($d->z++);
	var_dump ($d->z++);

	var_dump (++A::$q);
	var_dump (++A::$q);

	var_dump (++$s);
	var_dump (++$s);

	var_dump (++$d->z);
	var_dump (++$d->z);



?>
