/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test whether XML serialisation followed by deserialisation is the identity 
 */

#include <iostream>
#include "AST.h"
#include "config.h"
#include "process_ast/XML_unparser.h"
#include <parsing/XML_parser.h> 

using namespace std;

static void test_roundtrip (AST_php_script* php_script)
{
	#ifdef HAVE_XERCES

	// unparse once
	ostringstream xml_output1;
	XML_unparser xml_unparser1 (xml_output1);
	php_script->visit(&xml_unparser1);

	// reparse
	AST_php_script* reparsed1 = parse_ast_xml_buffer(new String(xml_output1.str()));

	// unparse once
	ostringstream xml_output2;
	XML_unparser xml_unparser2 (xml_output2);
	reparsed1->visit(&xml_unparser2);

	// reparse
	AST_php_script* reparsed2 = parse_ast_xml_buffer(new String(xml_output2.str()));

	if(php_script->equals(reparsed1) && php_script->equals(reparsed2))
	{
		printf("Success\n");
	}
	else
	{
		printf("Failure\n");
		XML_unparser unparser;
		php_script->visit(new XML_unparser ());
		reparsed1->visit(new XML_unparser ());
		reparsed2->visit(new XML_unparser ());
	}
	#else
	cout << "XML support not built-in" << endl;
	#endif
}


extern "C" void process_hir (AST_php_script* php_script)
{
	test_roundtrip (php_script);
}

