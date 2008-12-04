/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert the phc AST to DOT format
 */

#ifndef PHC_DOT_UNPARSER
#define PHC_DOT_UNPARSER

#include "AST_visitor.h"
#include "lib/Stack.h"

class DOT_unparser : public virtual AST::Visitor, virtual public GC_obj
{
private:
	Stack<int> node_stack;
	int new_node_id;

public:
	DOT_unparser(); 
	virtual ~DOT_unparser();

public:
	void visit_php_script(AST::PHP_script* in);
	void pre_node(AST::Node* in);
	void post_node(AST::Node* in);
	void pre_literal(AST::Literal* in);
	void pre_identifier(AST::Identifier* in);

public:
	void visit_marker(char const* name, bool value);
	void visit_null(char const* name_space, char const* type_id);
	void visit_null_list(char const* name_space, char const* type_id);
	void pre_list(char const* name_space, char const* type_id, int size);
	void post_list(char const* name_space, char const* type_id, int size);

protected:
	void new_node(char const* label, int line_number);
	void new_box(String* source_rep);
	void add_link(int target);

};

#endif // PHC_DOT_UNPARSER
