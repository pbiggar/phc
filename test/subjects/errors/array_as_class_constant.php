<?php
	// For some reason, arrays are not allowed as class constants

	class C
	{
		const X = array();	// { Error: Arrays are not allowed in class constants }
	}
?>
