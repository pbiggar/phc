/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test whether the tree is actually a tree (and not a graph) 
 */

#include "process_ir/General.h"
#include "Collect_all_pointers.h"
#include "pass_manager/Plugin_pass.h"
#include "AST_visitor.h"
#include "HIR_visitor.h"
#include "MIR_visitor.h"

/* We add this pass after every other pass in load(),
 * update the variables in run, and print out results in
 * exit (). */
static bool success = true;
static bool is_run = false;

template <class PHP_script, class Node, class Visitor>
void run (PHP_script* in)
{
	Collect_all_pointers<Node, Visitor> cap;
	in->visit(&cap);

	is_run = true;

	if(cap.all_pointers.size() != cap.unique_pointers.size())
	{
		success = false;
		
		// get a bit more information here. We want to print information if it all fails.
		cap.all_nodes.sort ();
		Node* last = NULL;
		for (typename List<Node*>::const_iterator n = cap.all_nodes.begin(); n != cap.all_nodes.end(); n++)
		{
			if (last)
			{
				if ((*n) == last)
				{
					printf ("Problem found: (%p)\n", *n);
					debug (*n);
					xdebug (*n);
				}
			}
			last = *n;
		}
	}
}


extern "C" void run_ast (AST::PHP_script* in, Pass_manager*) 
{ 
	run <AST::PHP_script, AST::Node, AST::Visitor> (in); 
}

extern "C" void run_hir (HIR::PHP_script* in, Pass_manager*) 
{
	run <HIR::PHP_script, HIR::Node, HIR::Visitor> (in);
}

extern "C" void run_mir (MIR::PHP_script* in, Pass_manager*) 
{
	run <MIR::PHP_script, MIR::Node, MIR::Visitor> (in); 
}

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_each_pass (pass);
}

extern "C" void unload ()
{
	if (is_run && success)
		printf("Success\n");
	else
		printf("Failure\n");
}
