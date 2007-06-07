/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * This transform tests the same number of pre_node and post_node calls are
 * done on an unmodified tree.
 */

#include "AST_visitor.h"

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
		if (count == 0)
		{
			printf("Success\n");
		}
		else 
		{
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
	Test_pre_vs_post_count t;
	script->visit(&t);
}
