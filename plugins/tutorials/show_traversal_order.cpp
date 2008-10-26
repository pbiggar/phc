/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "pass_manager/Plugin_pass.h"
#include "lib/demangle.h"
#include "AST_visitor.h"
#include "process_ir/General.h"

using namespace AST;
using namespace std;

class Show_traversal_order : public Visitor
{
public:
	void pre_node(Node* in)
	{
		cout << "pre_node on " << demangle(in, false) << endl;
	}

	void pre_commented_node(Commented_node* in)
	{
		cout << "pre_commented_node on " << demangle(in, false) << endl;
	}
	
	void pre_statement(Statement* in)
	{
		cout << "pre_statement on " << demangle(in, false) << endl;
	}
	
	void pre_if(If* in)
	{
		cout << "pre_if on " << demangle(in, false) << endl;
	}

	void children_if(If* in)
	{
		cout << "children_if" << endl;
		Visitor::children_if(in);
	}

	void post_node(Node* in)
	{
		cout << "post_node on " << demangle(in, false) << endl;
	}

	void post_commented_node(Commented_node* in)
	{
		cout << "post_commented_node on " << demangle(in, false) << endl;
	}
	
	void post_statement(Statement* in)
	{
		cout << "post_statement on " << demangle(in, false) << endl;
	}
	
	void post_if(If* in)
	{
		cout << "post_if on " << demangle(in, false) << endl;
	}
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, s("ast"));
}

extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
	in->visit (new Show_traversal_order ());
}
