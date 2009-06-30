<?php

	# test that rtrim is optimized out
	# { phc-option: --dump=codegen -O2 }
	# { phc-regex-output: !/rtrim/ }
	var_dump (rtrim ("asdasd", "fghfgh"));


?>
