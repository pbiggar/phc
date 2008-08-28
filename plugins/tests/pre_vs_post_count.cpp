/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * This transform tests the same number of pre_node and post_node calls are
 * done on an unmodified tree.
 */

#include "AST_visitor.h"
#include "HIR_visitor.h"
#include "MIR_visitor.h"
#include "pass_manager/Plugin_pass.h"
#include "pass_manager/Pass_manager.h"

static bool success = true;
static bool is_run = false;

template <class PHP_script, class Node, class Visitor>
class Test_pre_vs_post_count : public Visitor
{
private:
	int count;

public:
	void pre_php_script (PHP_script* in) { count = 0; }
	void post_php_script (PHP_script* in) { finish (); }
	void pre_node (Node* in) { count++; }
	void post_node (Node* out) { count--; }

	void finish ()
	{
		is_run = true;
		if (count != 0)
		{
			success = false;
			printf("Failure\n");
			printf("Count is %d\n", count);
		}
	}

};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_each_pass (pass);
}

extern "C" void run_ast (AST::PHP_script* in, Pass_manager* pm, String* option)
{
	in->visit (new Test_pre_vs_post_count <AST::PHP_script, AST::Node, AST::Visitor> ());
}

extern "C" void run_hir (HIR::PHP_script* in, Pass_manager* pm, String* option)
{
	in->visit (new Test_pre_vs_post_count <HIR::PHP_script, HIR::Node, HIR::Visitor> ());
}

extern "C" void run_mir (MIR::PHP_script* in, Pass_manager* pm, String* option)
{
	in->visit (new Test_pre_vs_post_count <MIR::PHP_script, MIR::Node, MIR::Visitor> ());
}

extern "C" void unload ()
{
	if (is_run && success)
		printf("Success\n");
	else
		printf("Failure\n");
}
