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
		// Only print the first time
		if (success)
			printf ("Failure\n");

		success = false;
		
		// get a bit more information here. We want to print information if it all fails.
		cap.all_pointers.sort ();
		Object* last = NULL;
		tfor_lci (&cap.all_pointers, Object, i)
		{
			if (last)
			{
				if ((*i) == last)
				{
					printf ("Problem found: (%p)\n", *i);
					if (Node* node = dynamic_cast<Node*> (*i))
					{
						// Print the nodes
						debug (node);
						xdebug (node);
					}
					else
					{
						// Find the owners of the attribute
						tfor_lci (&cap.all_nodes, Node, n)
						{
							AttrMap::const_iterator a;
							for(a = (*n)->attrs->begin(); a != (*n)->attrs->end(); a++)
							{
								if ((*a).second == *i)
								{
									printf ("In parent node: (%p), attribute name %s\n", *n, (*a).first.c_str ());
									debug (*n);
									xadebug (*n);
								}
							}

						}

					}
				}
			}
			last = *i;
		}
	}
}


extern "C" void run_ast (AST::PHP_script* in, Pass_manager*, String* option)
{ 
	run <AST::PHP_script, AST::Node, AST::Visitor> (in);
}

extern "C" void run_hir (HIR::PHP_script* in, Pass_manager*, String* option)
{
	run <HIR::PHP_script, HIR::Node, HIR::Visitor> (in);
}

extern "C" void run_mir (MIR::PHP_script* in, Pass_manager*, String* option)
{
	run <MIR::PHP_script, MIR::Node, MIR::Visitor> (in);
}

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_each_pass (pass);
}

extern "C" void unload ()
{
	if (!is_run)
		printf("Failure\n");
	else if (success)
		printf("Success\n");
	else
	{
		; // Failure will already be printed above
	}
}
