/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert the phc AST to XML format
 */
#include <ostream>

#include "cmdline.h"

#include "XML_unparser.h"
#include "lib/Object.h"

// See comment in XML_unparser::print_indent
extern gengetopt_args_info args_info;
char* get_args_info_tab ()
{
	return args_info.tab_arg;
}


using namespace std;

XML_unparser_state::XML_unparser_state (ostream& os, bool print_attrs)
: os (os)
, print_attrs (print_attrs)
, indent (0)
{
}

void
XML_unparser_state::print_indent ()
{
	// Because this is a header, we cant put extern args_info in the file.
	// However, adding it in this scope is also confusing, since the compiler
	// may think it has internal linkage, when it actually has external (a
	// theory, I'm not sure of the exact problem). Anyway, the solution is to
	// put the access to args_info in a separate file, and access it that way.
	for(int i = 0; i < indent; i++)
		os << get_args_info_tab ();
}

void
xml_unparse (AST::Node* in, XML_unparser_state* state)
{
	in->visit (new AST_XML_unparser (state));
}

void xml_unparse (HIR::Node* in, XML_unparser_state* state)
{
	in->visit (new HIR_XML_unparser (state));
}

void xml_unparse (MIR::Node* in, XML_unparser_state* state)
{
	in->visit (new MIR_XML_unparser (state));
}

void xml_unparse (IR::Node* in, XML_unparser_state* state)
{
	if (isa<AST::Node> (in))
		xml_unparse (dyc<AST::Node> (in), state);
	else if (isa<HIR::Node> (in))
		xml_unparse (dyc<HIR::Node> (in), state);
	else
		xml_unparse (dyc<MIR::Node> (in), state);
}


void xml_unparse (AST::Node* in, ostream& os, bool print_attrs)
{
	in->visit (new AST_XML_unparser (os, print_attrs));
}

void xml_unparse (HIR::Node* in, ostream& os, bool print_attrs)
{
	in->visit (new HIR_XML_unparser (os, print_attrs));
}

void xml_unparse (MIR::Node* in, ostream& os, bool print_attrs)
{
	in->visit (new MIR_XML_unparser (os, print_attrs));
}

void xml_unparse (IR::PHP_script* in, ostream& os, bool print_attrs)
{
	if (isa<AST::PHP_script> (in))
		xml_unparse (dyc<AST::Node> (in), os, print_attrs);
	else if (isa<HIR::PHP_script> (in))
		xml_unparse (dyc<HIR::Node> (in), os, print_attrs);
	else
		xml_unparse (dyc<MIR::Node> (in), os, print_attrs);
}
