/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test whether the tree is actually a tree (and not a graph) 
 */

#include "Collect_all_pointers.h"

static void test_linear (AST_php_script* php_script)
{
	Collect_all_pointers cap;
	php_script->visit(&cap);

	if(cap.all_pointers.size() == cap.unique_pointers.size())
		printf("Success\n");
	else
		printf("Failure\n");
}

extern "C" void process_hir (AST_php_script* php_script)
{
	test_linear (php_script);
}


extern "C" void process_ast (AST_php_script* php_script)
{
	test_linear (php_script);
}
