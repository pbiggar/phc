<?php

	for ($i = 0; $i < 10; $i++)
	{
		define ("MY_CONSTANT", -50);
	}

	var_dump (MY_CONSTANT);

	// And now with variables.

	for ($i = 0; $i < 10; $i++)
	{
		define ("MY_OTHER_CONSTANT", $i);
	}

	var_dump (MY_OTHER_CONSTANT);


?>
