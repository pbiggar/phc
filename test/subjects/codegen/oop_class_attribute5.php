<?php
	class C
	{
		var $x = array(1,2,3); 
	}

	eval('$c = new C(); var_dump($c);');
?>
