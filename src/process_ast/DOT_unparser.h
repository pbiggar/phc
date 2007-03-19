/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert the phc AST to DOT format
 */

#ifndef PHC_DOT_UNPARSER
#define PHC_DOT_UNPARSER

#include "process_ast/Visit_everything.h"
#include <stack>
#include <map>

class DOT_unparser : public virtual Visit_everything
{
private:
	void show_source_rep(String* source_rep);

	stack<int> node_stack;
	map<Object*, int> node_ids;
	int new_node_id;

public:
	DOT_unparser(); 
	virtual ~DOT_unparser(); 

public:
	// These need to be declared here because they are pure virtual in the
	// base class
	void visit_null(char* type_id);
	void visit_marker(char* name, bool value);

public:
	void pre_literal(AST_literal* in);
	void pre_identifier(AST_identifier* in);
	void post_node(AST_node* in);
	void pre_node(AST_node* in);
};

#endif // PHC_DOT_UNPARSER
