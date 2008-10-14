/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test whether cloning works 
 */

#include "Collect_all_pointers.h"
#include "process_ast/AST_unparser.h"
#include "process_hir/HIR_unparser.h"
#include "process_mir/MIR_unparser.h"
#include "pass_manager/Plugin_pass.h"

static bool success = true;
static bool is_run = false;

using namespace std;

template <class PHP_script, class Node, class Unparser, class Visitor>
void run (PHP_script* in)
{
	is_run = true;

	// get the first script
	Collect_all_pointers<Node, Visitor> orig_cap;
	in->visit(&orig_cap);

	// make a duplicate
	PHP_script* dup_script = in->clone();
	Collect_all_pointers<Node, Visitor> dup_cap;
	dup_script->visit(&dup_cap);

	// Compare if the two scripts are the same
	if(!in->equals(dup_script))
	{
		ostringstream orig_unparsed, dup_unparsed;
		Unparser a(orig_unparsed), b(dup_unparsed);
		a.unparse (in);
		b.unparse (dup_script);

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
}

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_each_pass (pass);
}

extern "C" void run_ast (AST::PHP_script* in, Pass_manager*, String* option) { run <AST::PHP_script, AST::Node, AST_unparser, AST::Visitor> (in); }
extern "C" void run_hir (HIR::PHP_script* in, Pass_manager*, String* option) { run <HIR::PHP_script, HIR::Node, HIR_unparser, HIR::Visitor> (in); }
extern "C" void run_mir (MIR::PHP_script* in, Pass_manager*, String* option) { run <MIR::PHP_script, MIR::Node, MIR_unparser, MIR::Visitor> (in); }

extern "C" void unload ()
{
	if (is_run && success)
		printf("Success\n");
	else
		printf("Failure\n");
}


