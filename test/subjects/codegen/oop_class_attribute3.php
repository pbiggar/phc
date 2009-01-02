<?php
	// When a previously undefined variable is used as an object, it becomes
	// an instance of StdClass. Hence, this test is semantically identical to
	// oop_class_attribute2.php

	$c->a = 1;
	var_dump($c);
?>
