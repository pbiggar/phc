<?php

	// Reported by Stig Vestøl (Vestøl Data)
	// Segfaults after installing as an extension, which is hard to test.

	class Superclass
	{
	}

	class MyClass extends SuperClass
	{
	}

?>
