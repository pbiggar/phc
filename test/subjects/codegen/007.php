<?php
	function factorial($n)
	{
		if($n == 0)
			return 1;
		else
			return $n * factorial($n - 1);
	}

	function main()
	{
		var_dump(factorial(15));
	}
?>
