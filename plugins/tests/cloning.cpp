/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test whether cloning works 
 */

#include "Collect_all_pointers.h"
#include "process_ast/PHP_unparser.h"

extern "C" void process_ast(AST_php_script* orig_script)
{
	bool success = true;

	// get the first script
	Collect_all_pointers orig_cap;
	orig_script->visit(&orig_cap);

	// make a duplicate
	AST_php_script* dup_script = orig_script->clone();
	Collect_all_pointers dup_cap;
	dup_script->visit(&dup_cap);

	// Compare if the two scripts are the same
	if(!orig_script->equals(dup_script))
	{
		ostringstream orig_unparsed, dup_unparsed;
		PHP_unparser a(orig_unparsed), b(dup_unparsed);
		orig_script->visit(&a);
		dup_script->visit(&b);

		printf("Failure\n");
		printf("Unparsing yields different results\n");
		cout << orig_unparsed.str();
		cout << dup_unparsed.str();
		success = false;
	}

	// Make sure the duplicated tree does not contain any pointers in the 
	// original tree
	list<Object*>::const_iterator i;
	for(i = dup_cap.all_pointers.begin(); i != dup_cap.all_pointers.end(); i++)
	{
		if(orig_cap.unique_pointers.find(*i) != orig_cap.unique_pointers.end())
		{
			printf("Failure\n");
			printf("Cloned tree contains pointers from original tree\n");
			success = false;
		}
	}
	
	if (success == true)
		printf("Success\n");
}

