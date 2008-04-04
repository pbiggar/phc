/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test whether we create nodes without attributes.
 */

#include "process_ir/General.h"
#include "pass_manager/Plugin_pass.h"
#include "AST_visitor.h"
#include "HIR_visitor.h"
#include "MIR_visitor.h"

template <class Node, class Visitor>
class Lost_attributes : public Visitor
{
private:
	bool init;

public:
	Lost_attributes (bool init = false) : init (init) { }

	void pre_node (Node* in)
	{
		if (init)
		{
			in->attrs->set_true ("phc.lost_attributes.test");
		}
		else if (!in->attrs->is_true ("phc.lost_attributes.test"))
		{
			debug (in);
			xadebug (in);
			cout << "Failure" << endl;
			exit (-1);
		}
	}
};

extern "C" void run_ast (AST::PHP_script* in, Pass_manager*, String* option)
{
	static bool first = true;
	if (first)
	{
		in->visit (new Lost_attributes<AST::Node, AST::Visitor> (true));
		first = false;
	}
	in->visit (new Lost_attributes<AST::Node, AST::Visitor>);
}

extern "C" void run_hir (HIR::PHP_script* in, Pass_manager*, String* option)
{
	in->visit (new Lost_attributes<HIR::Node, HIR::Visitor>);
}

extern "C" void run_mir (MIR::PHP_script* in, Pass_manager*, String* option)
{
	in->visit (new Lost_attributes<MIR::Node, MIR::Visitor>);
}

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_each_pass (pass);
}

extern "C" void unload ()
{
	printf("Success\n");
}
