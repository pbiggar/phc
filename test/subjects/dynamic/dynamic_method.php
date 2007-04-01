<?php

	class A
	{
		function c()
		{
			if ($a)
			{
				function a()
				{
					print "First a\n";
				}
			}
			else
			{
				function a()
				{
					print "Second a\n";
				}
			}
		}
	}

	$a = new A();
	$a->c();
	a();

?>
