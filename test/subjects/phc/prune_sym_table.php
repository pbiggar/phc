<?php

	// { phc-option: --dump=generate-c }
	// { phc-regex-output: !/global \$x/ }
	function x()
	{
		global $x;
	}

?>
