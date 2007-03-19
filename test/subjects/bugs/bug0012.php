<?php
	# Add line of code to current opcode handler
	$opcodes["code"] .= $line;

	# I think this was actually a bug with gcc. But we'll add it just in case.
	# This works if any of the following are removed: the comment, the indexing
	# by a string, and the dot equals
?>
