/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * This transform tests the same number of pre_node and post_node calls are
 * done on an unmodified tree.
 */

#include "AST_visitor.h"
#include "process_ast/Pass_manager.h"

static bool success = true;
static bool is_run = false;
class Test_pre_vs_post_count : public AST_visitor
{
private:
	int count;

public:
	void pre_php_script(AST_php_script* in)
	{
		count = 0;
	}

	void post_php_script(AST_php_script* in)
	{
		is_run = true;
		if (count != 0)
		{
			success = false;
			printf("Failure\n");
			printf("Count is %d\n", count);
		}
	}

	void pre_node(AST_node* in)
	{
		count++;
	}

	void post_node(AST_node* out)
	{
		count--;
	}
};

extern "C" void process_hir (AST_php_script* script)
{
}


extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_each_pass (pass);
}

extern "C" void run (AST_php_script* in, Pass_manager* pm)
{
	in->visit(new Test_pre_vs_post_count ());
}

extern "C" void unload ()
{
	if (is_run && success)
		printf("Success\n");
	else
		printf("Failure\n");
}


