<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Read all the passes of the compiler, then add a pass to test each to
 * the pass queue.
 */

$pass_list = get_pass_list ();
$prev = "BasicParseTest";
foreach ($pass_list as $pass_name)
{
	$tests[] = new CompareWithPHP ("Interpret_$pass_name", 
											"--dump=$pass_name", $prev);

	$prev = "Interpret_$pass_name";
}
	

function get_pass_list ()
{
	list ($out, $err, $exit) = complete_exec ("src/phc --list-passes");
	assert ($out and $err === "" and $exit === 0);

	preg_match_all ("/([a-zA-Z-_0-9]+)\s+\((enabled|disabled)\s+- (AST|HIR|MIR|LIR)\)\s+.+/", $out, $matches);

	return $matches[1];
}


?>
