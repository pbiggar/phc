/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Perform a number of whole-program analyses simulteneously.
 */


#include "BCCH_aliasing.h"
#include "Callgraph.h"
#include "CCP.h"
#include "Constant_state.h"
#include "Include_analysis.h"
#include "Type_inference.h"
#include "VRP.h"
#include "WPA.h"
#include "Whole_program.h"

using namespace MIR;
using namespace boost;

Whole_program::Whole_program ()
{
	register_analysis ("BCCH_aliasing", new BCCH_aliasing);
	register_analysis ("Callgraph", new Callgraph);
	register_analysis ("CCP", new CCP);
	register_analysis ("Constant_state", new Constant_state);
	register_analysis ("Include_analysis", new Include_analysis);
	register_analysis ("Type_inference", new Type_inference);
	register_analysis ("VRP", new VRP);
}

void
Whole_program::run (MIR::PHP_script* in)
{
	foreach (Statement* stmt, *in->statements)
	{
		if (Method* m = dynamic_cast<Method*> (stmt))
			functions[*m->signature->method_name->value] = m;

		else if (Class_def* c = dynamic_cast<Class_def*> (stmt))
			classes[*c->class_name->value] = c;

	}

	CFG* cfg = new CFG (functions["__MAIN__"]);
	evaluate_function (cfg);
}


void
Whole_program::evaluate_function (CFG* in)
{
	// TODO: not sure where to put the iteration yet. Just do the first few statements, and it should be a little clearer.

	Basic_block* entry = in->get_entry_bb ();
	foreach (Basic_block* succ, *entry->get_successors ())
	{
		WPA* wpa;
		string name;
		foreach (tie (name, wpa), analyses)
		{
			wpa->eval_bb (succ);
		}
	}
}

void
Whole_program::register_analysis (string name, WPA* analysis)
{
	assert (!analyses.has (name));
	analyses[name] = analysis;
}
