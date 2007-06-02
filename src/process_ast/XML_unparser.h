/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert the phc AST to XML format
 */

#ifndef PHC_XML_UNPARSER
#define PHC_XML_UNPARSER

#include "AST_visitor.h"

// these are split so they're easy to call from the debugger
void xdebug (AST_node* in);
void xadebug (AST_node* in); // print attrs

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
	void visit_marker(char const* name, bool value);
	void visit_null(char const* type_id);
	void visit_null_list(char const* type_id);
	void pre_list(char const* type_id, int size);
	void post_list(char const* type_id, int size);

public:
	void pre_node(AST_node* in);
	void post_node(AST_node* in);
	void pre_identifier(AST_identifier* in);
	void pre_literal(AST_literal* in);

};

#endif // PHC_XML_UNPARSER
