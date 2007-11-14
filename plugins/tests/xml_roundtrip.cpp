/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test whether XML serialisation followed by deserialisation is the identity 
 */

#include <iostream>
#include "config.h"
#include "process_ir/XML_unparser.h"
#include "parsing/XML_parser.h" 
#include "pass_manager/Pass_manager.h" 

using namespace std;
using namespace AST;

static bool success = true;
static bool is_run = false;

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_each_pass (pass);
}

extern "C" void run (AST_php_script* in, Pass_manager* pm)
{
#ifdef HAVE_XERCES
	is_run = true;

	// unparse once
	ostringstream xml_output1;
	AST_XML_unparser xml_unparser1 (xml_output1);
	in->visit(&xml_unparser1);

	// reparse
	AST_php_script* reparsed1 = parse_ast_xml_buffer(new String(xml_output1.str()));

	// unparse a second time
	ostringstream xml_output2;
	AST_XML_unparser xml_unparser2 (xml_output2);
	reparsed1->visit(&xml_unparser2);

	// reparse
	AST_php_script* reparsed2 = parse_ast_xml_buffer(new String(xml_output2.str()));

	if (not (in->equals(reparsed1) && in->equals(reparsed2)))
	{
		printf("Failure\n");
		AST_XML_unparser unparser;
		in->visit (new AST_XML_unparser ());
		reparsed1->visit (new AST_XML_unparser ());
		reparsed2->visit (new AST_XML_unparser ());
	}
#else
	cout << "XML support not built-in" << endl;
#endif

}

extern "C" void unload ()
{
	if (is_run && success)
		printf("Success\n");
	else
		printf("Failure\n");
}
