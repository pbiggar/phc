<?php

	function test ()
	{

		// Tests sccp into a binop
		// { phc-option: -O1 --dump=outssa }

		// Check propagation into bin_ops
		// { phc-regex-output: /5 </ }
		$const = 5;
		if ($const < rand ())
		{
			print `ls`; // side-effecting
		}

		// Check propagation into unary ops
		// { phc-regex-output: !/\$const2/ }
		$const2 = 6;
		if (!$const2 && rand ())
		{
			print `ls`; // side-effecting
		}


		// Check that dead vars that go through PHIs are removed
		// { phc-regex-output: !/\$const3/ }

		// Check that getrandmax is optimized out
		// { phc-regex-output: !/getrandmax/ }

		while (rand () > getrandmax() / 2)
		{
			$const3 = "string";
			print `ls $const3`;
		}


		// Check we've removed all the !s
		// { phc-regex-output: !/!/ }
	}

?>
