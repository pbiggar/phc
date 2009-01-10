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
// TODO: string value analysis
// TODO: error_reporting isnt important during analysis, only after, I think. But what 

using namespace MIR;

Whole_program::Whole_program()
{
	register_analysis (new BCCH_aliasing);
	register_analysis (new Call_graph);
	register_analysis (new CCP);
	register_analysis (new Constant_state);
	register_analysis (new Include_path_state);
	register_analysis (new Type_inference);
	register_analysis (new VRP);
}

void
Whole_program::run (PHP_script* in)
{
	foreach (Statement* stmt, in->statements)
	{
		if (Method* m = dynamic_cast<Method*> (in))
			functions[*m->signature->method_name->value] = m;

		else if (Class_def* c = dynamic_cast<Class_def*> (in))
			classes[*c->class_name->value] = c;

		else
			PUNT;
	}

	evaluate_function (new CFG (functions["__MAIN__"]));
}

void
Whole_program::evaluate_function (CFG* cfg)
{
	// TODO: not sure how the visitors will work exactly. Just pass in the first
	// BB to each of the analyses for now.
	
	// TODO: need to pass 'is_global_scope' somehow.

	
	Basic_block* entry = cfg->get_entry_bb ();
	foreach (Basic_block* succ, *entry->get_successors ())
	{
		string name;
		WPA* analysis;
		foreach (tie (name, analysis), *analyses)
		{
			analysis->eval_bb (succ);
		}
	}
}
