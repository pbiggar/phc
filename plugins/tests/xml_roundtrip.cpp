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
#include "pass_manager/Plugin_pass.h" 

using namespace std;

static bool success = true;
static bool is_run = false;

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_each_pass (pass);
}

template <class PHP_script, class XML_unparser, class XML_parser>
void run (PHP_script* in)
{
#ifdef HAVE_XERCES
	is_run = true;
	XML_parser parser;

	// unparse once
	ostringstream output1;
	XML_unparser unparser1 (output1);
	in->visit(&unparser1);

	// reparse
	PHP_script* reparsed1 = parser.parse_xml_buffer (new String(output1.str()));

	// unparse a second time
	ostringstream output2;
	XML_unparser unparser2 (output2);
	reparsed1->visit(&unparser2);

	// reparse
	PHP_script* reparsed2 = parser.parse_xml_buffer (new String(output2.str()));

	if (not (in->equals(reparsed1) && in->equals(reparsed2)))
	{
		printf("Failure\n");
		in->visit (new XML_unparser ());
		reparsed1->visit (new XML_unparser ());
		reparsed2->visit (new XML_unparser ());
	}
#else
	cout << "XML support not built-in" << endl;
#endif

}


extern "C" void run_ast (AST::PHP_script* in, Pass_manager*)
{
	run <AST::PHP_script, AST_XML_unparser, AST_XML_parser> (in);
}

extern "C" void run_hir (HIR::PHP_script* in, Pass_manager*)
{
	run <HIR::PHP_script, HIR_XML_unparser, HIR_XML_parser> (in);
}

extern "C" void run_mir (MIR::PHP_script* in, Pass_manager*)
{
	run <MIR::PHP_script, MIR_XML_unparser, MIR_XML_parser> (in);
}

extern "C" void unload ()
{
	if (is_run && success)
		printf("Success\n");
	else
		printf("Failure\n");
}
