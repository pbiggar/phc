/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test whether the tree is actually a tree (and not a graph) 
 */

#include "Collect_all_pointers.h"

extern "C" void process_ast(AST_php_script* script)
{
	Collect_all_pointers cap;
	script->visit(&cap);

	if(cap.all_pointers.size() == cap.unique_pointers.size())
		printf("Success\n");
	else
		printf("Failure\n");
}

