/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert the phc AST to XML format
 */

#ifndef PHC_XML_UNPARSER
#define PHC_XML_UNPARSER

#include <iostream>

#include "process_ir/IR.h"

class XML_unparser_state
{
public:
	ostream& os;
	bool print_attrs;
	int indent;

public:
	XML_unparser_state (ostream& os, bool print_attrs);
	void print_indent();
};

void xml_unparse (AST::Node*, XML_unparser_state* state);
void xml_unparse (HIR::Node*, XML_unparser_state* state);
void xml_unparse (MIR::Node*, XML_unparser_state* state);
void xml_unparse (IR::Node*, XML_unparser_state* state);
void xml_unparse (AST::Node*, ostream& os = cout, bool print_attrs = true);
void xml_unparse (HIR::Node*, ostream& os = cout, bool print_attrs = true);
void xml_unparse (MIR::Node*, ostream& os = cout, bool print_attrs = true);
void xml_unparse (IR::PHP_script*, ostream& os = cout, bool print_attrs = true);


#endif // PHC_XML_UNPARSER
