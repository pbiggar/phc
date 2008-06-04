<?php
	// Reduced with command line 'test/framework/reduce -v -v -i mir -u test/subjects/codegen/masquarading_int_keys.php'

	/* There seems to be a bug in ArrayIterator, where it refuses to print array
	 * items with empty strings for keys. This means the test refuses to work,
	 * even though later tests succeed. */
	$x["ASDASD"] = "ASDASD";
	$x[$TLE27] = $TLE27;

	foreach ($x as $key => $value) {
		$TSe1 = var_dump($value);
	}
?>
