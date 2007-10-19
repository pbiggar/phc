/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test whether the tree is actually a tree (and not a graph) 
 */

#include "Collect_all_pointers.h"
#include "pass_manager/Pass_manager.h"

/* We add this pass after every other pass in load(),
 * update the variables in run, and print out results in
 * exit (). */
static bool success = true;
static bool is_run = false;

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_each_pass (pass);
}


extern "C" void run (AST_php_script* in, Pass_manager* pm)
{
	Collect_all_pointers cap;
	in->visit(&cap);

	is_run = true;

	if(cap.all_pointers.size() != cap.unique_pointers.size())
		success = false;
}

extern "C" void unload ()
{
	if (is_run && success)
		printf("Success\n");
	else
		printf("Failure\n");
}


