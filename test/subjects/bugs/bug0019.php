<?php

	/* This is to check the php unparser unparsing \x00 by itself */

	/* this has to be by itself, or it will benefit from other stirngs being
	 * picked up as being escaped */
	echo "\x00";
	echo "\000";

	/* no harm checking other permutations while we're here */
	echo "\000 \001";
	echo "\001 \000";

	echo "\x00 \x01";
	echo "\x01 \x00";

	echo "\x00 \001";
	echo "\x01 \000";

	echo "\000 \x01";
	echo "\001 \x00";
?>
