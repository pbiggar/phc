/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "AST_visitor.h"
#include "lib/demangle.h"

class Show_traversal_order : public AST_visitor
{
public:
	void pre_node(AST_node* in)
	{
		cout << "pre_node on " << demangle(in) << endl;
	}

	void pre_commented_node(AST_commented_node* in)
	{
		cout << "pre_commented_node on " << demangle(in) << endl;
	}
	
	void pre_statement(AST_statement* in)
	{
		cout << "pre_statement on " << demangle(in) << endl;
	}
	
	void pre_if(AST_if* in)
	{
		cout << "pre_if on " << demangle(in) << endl;
	}

	void children_if(AST_if* in)
	{
		cout << "children_if" << endl;
		AST_visitor::children_if(in);
	}

	void post_node(AST_node* in)
	{
		cout << "post_node on " << demangle(in) << endl;
	}

	void post_commented_node(AST_commented_node* in)
	{
		cout << "post_commented_node on " << demangle(in) << endl;
	}
	
	void post_statement(AST_statement* in)
	{
		cout << "post_statement on " << demangle(in) << endl;
	}
	
	void post_if(AST_if* in)
	{
		cout << "post_if on " << demangle(in) << endl;
	}
};

extern "C" void process_ast(AST_php_script* in)
{
	Show_traversal_order sto;
	in->visit(&sto);
}
