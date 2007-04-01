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

extern "C" void process_ast(AST_php_script* script)
{
	#ifdef HAVE_XERCES
	ostringstream xml_output;
	XML_unparser xml_unparser(xml_output);
	script->visit(&xml_unparser);
	AST_php_script* reparsed = parse_ast_xml_buffer(new String(xml_output.str()));

	if(script->equals(reparsed))
	{
		printf("Success\n");
	}
	else
	{
		printf("Failure\n");
		XML_unparser unparser;
		script->visit(&unparser);
		reparsed->visit(&unparser);
	}
	#else
	cout << "XML support not built-in" << endl;
	#endif
}
