<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compares phc's internal values with the source representations of them
 */

array_push($tests, new SourceVsSemanticTest ());
class SourceVsSemanticTest extends PluginTest
{
	function __construct ()
	{
		parent::__construct("source_vs_semantic_values");
	}

	function get_dependent_test_names ()
	{
		return array ("BasicParseTest");
	}

	function get_command_line ($subject)
	{
		global $phc, $php, $plugin_dir;
		return "$phc --run $plugin_dir/tests/source_vs_semantic_values.la $subject 2>&1 | $php -d memory_limit=128M 2>&1";
	}
	
}


