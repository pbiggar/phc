<?php

	// Ignore some vars
	unset ($HTTP_COOKIE_VARS, $HTTP_ENV_VARS, $HTTP_GET_VARS);
	unset ($HTTP_POST_FILES, $HTTP_POST_VARS, $HTTP_SERVER_VARS);
	unset ($_COOKIE, $_ENV, $_GET, $_SERVER, $_FILES, $_REQUEST, $_POST);
	unset ($argv, $argc);


	define (SV, "string"); // string value
	define (IV, "int"); // int value
	define (SI, "5"); // string index
	define (II, 5); // int index

	echo ("ARRAY INDEXING - int first\n");
	$a[II] = IV;
	$a[SI] = SV;
	var_dump ($a);
	unset ($a);

	echo ("ARRAY INDEXING - string first\n");
	$a[SI] = SV;
	$a[II] = IV;
	var_dump ($a);
	unset ($a);

	echo ("VAR-FIELDS - string first\n");
	$a = new stdclass;
	$a->{II} = IV;
	$a->{SI} = SV;
	var_dump ($a);
	unset ($a);

	echo ("VAR-FIELDS - int first\n");
	$a = new stdclass;
	$a->{II} = IV;
	$a->{SI} = SV;
	var_dump ($a);
	unset ($a);

	echo ("VAR-VARS - int first\n");
	${II} = IV;
	${SI} = SV;
	var_dump ($GLOBALS);
	unset (${II}, ${SI});

	echo ("VAR-VARS - string first\n");
	${SI} = SV;
	${II} = IV;
	var_dump ($GLOBALS);
	unset (${II}, ${SI});

?>
