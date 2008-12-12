<?php

	var_dump (include_once ("add.php"));
	var_dump (include_once ("add.php"));

	var_dump (require_once ("just_int.php"));
	var_dump (require_once ("just_int.php"));

	var_dump (include ("just_int.php"));
	var_dump (require ("add.php"));

	var_dump (include ("not_a_real_file.php"));
	var_dump (include_once ("not_a_real_file.php"));
	var_dump (require_once ("not_a_real_file.php"));

?>
