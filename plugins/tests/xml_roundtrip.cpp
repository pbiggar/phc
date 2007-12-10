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

template <class PHP_script, class XML_unparser>
void run (PHP_script* in)
{
#ifdef HAVE_XERCES
	is_run = true;

	// unparse once
	ostringstream xml_output1;
	XML_unparser xml_unparser1 (xml_output1);
	in->visit(&xml_unparser1);

	// reparse
	PHP_script* reparsed1 = parse_ast_xml_buffer(new String(xml_output1.str()));

	// unparse a second time
	ostringstream xml_output2;
	XML_unparser xml_unparser2 (xml_output2);
	reparsed1->visit(&xml_unparser2);

	// reparse
	PHP_script* reparsed2 = parse_ast_xml_buffer(new String(xml_output2.str()));

	if (not (in->equals(reparsed1) && in->equals(reparsed2)))
	{
		printf("Failure\n");
		XML_unparser unparser;
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
	run <AST::PHP_script, AST_XML_unparser> (in);
}

extern "C" void run_hir (HIR::PHP_script* in, Pass_manager*)
{
	// TODO These functions wont work until parse_ast_xml_buffer returns an IR
	assert (0);
//	run <HIR::PHP_script, HIR_XML_unparser> (in);
}

extern "C" void run_mir (MIR::PHP_script* in, Pass_manager*)
{
	assert (0);
//	run <MIR::PHP_script, MIR_XML_unparser> (in);
}

extern "C" void unload ()
{
	if (is_run && success)
		printf("Success\n");
	else
		printf("Failure\n");
}
