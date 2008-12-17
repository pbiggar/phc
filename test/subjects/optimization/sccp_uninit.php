<?php

	// { phc-option: -O1 --dump=outssa } 
	// { phc-regex-output: !/TRUE/ }
	// { phc-regex-output: /FALSE/ }


	function test ()
	{
		if ($x)
		{
			echo "TRUE\n";
		}
		else
		{
			echo "FALSE\n";
		}
	}

	test ();
?>
