<?php
	class C
	{
		static $s = 2;
	}

	eval('var_dump(C::$s);');
?>
