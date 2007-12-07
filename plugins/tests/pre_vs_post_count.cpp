/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * This transform tests the same number of pre_node and post_node calls are
 * done on an unmodified tree.
 */

#include "AST_visitor.h"
#include "HIR_visitor.h"
#include "pass_manager/Plugin_pass.h"

static bool success = true;
static bool is_run = false;

class Test_pre_vs_post_count : public AST::Visitor, public HIR::Visitor
{
private:
	int count;

public:
	void pre_php_script (AST::PHP_script* in) { count = 0; }
	void post_php_script (AST::PHP_script* in) { finish (); }
	void pre_node (AST::Node* in) { count++; }
	void post_node (AST::Node* out) { count--; }
	void pre_php_script (HIR::PHP_script* in) { count = 0; }
	void post_php_script (HIR::PHP_script* in) { finish (); }
	void pre_node (HIR::Node* in) { count++; }
	void post_node (HIR::Node* out) { count--; }



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

extern "C" void run_ast (AST::PHP_script* in, Pass_manager* pm)
{
	in->visit (new Test_pre_vs_post_count ());
}

extern "C" void run_hir (HIR::PHP_script* in, Pass_manager* pm)
{
	in->visit (new Test_pre_vs_post_count ());
}



extern "C" void unload ()
{
	if (is_run && success)
		printf("Success\n");
	else
		printf("Failure\n");
}
