<?php
	class C
	{
		static $s;
	}

	eval('C::$s = 1; var_dump(C::$s);');
?>
