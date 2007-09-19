<?php
	// For some reason, arrays are not allowed as class constants

	class C
	{
		const X = array();	// {Fatal error: Arrays are not allowed in class constants}
	}
?>
