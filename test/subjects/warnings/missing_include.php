<?php
	// { phc-option: --include }

	include "non_existant_file.php"; // { phc-warning: File non_existant_file.php could not be included, and will be included at run-time }

?>
