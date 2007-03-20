/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert the phc AST to XML format
 */

#ifndef PHC_XML_UNPARSER
#define PHC_XML_UNPARSER

#include "AST_visitor.h"

class XML_unparser : public AST_visitor 
{
protected:
	ostream& os;
	int indent;
	bool print_attrs;

	void print_indent();
	bool needs_encoding(String* str);

public:
	XML_unparser(ostream& os = cout, bool print_attrs = true); 
	virtual ~XML_unparser();

public:
	// These need to be declared here because they are pure virtual in the
	// base class
	void visit_null(char* type_id);
	void visit_marker(char* name, bool value);

public:
	void pre_node(AST_node* in);
	void post_node(AST_node* in);
	void pre_identifier(AST_identifier* in);
	void pre_literal(AST_literal* in);

};

#endif // PHC_XML_UNPARSER
