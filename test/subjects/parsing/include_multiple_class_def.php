<?php

	// Test tp see of the class definition gets included more than once, leading
	// to an error. It doesnt. This shows that it's appropriate to include class
	// and function definitions where the include is, as opposed to in global scope.

	if ($x == 6)
		include "included_multiple_class_def.php";
	else
		include "included_multiple_class_def.php";

?>
