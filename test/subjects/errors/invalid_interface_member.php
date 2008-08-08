<?php

	interface Foo 
	{
		var $bold; # {phc-error: Interfaces may not include member variables } 
	}

?>
