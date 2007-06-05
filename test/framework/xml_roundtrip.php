<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check the XML output of a script is the same as if it was parsed from XML
 */

array_push($tests, new XMLRoundtrip());
class XMLRoundtrip extends PluginTest
{
	function __construct ()
	{
		parent::__construct("xml_roundtrip");
	}

	function get_dependent_test_names ()
	{
		return array ("BasicParseTest");
	}

	function check_prerequisites ()
	{
		global $xerces_compiled_in;
		return parent::check_prerequisites () and
			$xerces_compiled_in != 'no';
	}
	
}


