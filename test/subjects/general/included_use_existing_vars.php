<?php

	var_dump($i1);
	var_dump($i2);
	if($i1 !== "some value" and $i2 !== "another value")
	{
		fail(__FILE__, __LINE__, "using variables inncluded file");
	}

?>
