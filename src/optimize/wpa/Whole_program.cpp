/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Perform a number of whole-program analyses simulteneously.
 */

#include "process_ir/General.h"

#include "BCCH_aliasing.h"
#include "Callgraph.h"
#include "CCP.h"
#include "Constant_state.h"
#include "Include_analysis.h"
#include "Type_inference.h"
#include "VRP.h"
#include "WPA.h"
#include "Whole_program.h"
#include "optimize/Oracle.h"
#include "optimize/Edge.h"

using namespace MIR;
using namespace boost;

Whole_program::Whole_program ()
{
	register_analysis ("BCCH_aliasing", new BCCH_aliasing (this));
//	register_analysis ("Callgraph", new Callgraph);
//	register_analysis ("CCP", new CCP);
//	register_analysis ("Constant_state", new Constant_state);
//	register_analysis ("Include_analysis", new Include_analysis);
//	register_analysis ("Type_inference", new Type_inference);
//	register_analysis ("VRP", new VRP);
}

void
Whole_program::run (MIR::PHP_script* in)
{
	evaluate_method_info (Oracle::get_method_info (s("__MAIN__")));
}


void
Whole_program::evaluate_function (CFG* cfg)
{
	// This is very similar to run() from Sparse_conditional_visitor, except
	// that it isnt sparse.

	WPA* wpa;
	string name;

	cfg->dump_graphviz (NULL);



	// 1. Initialize:
//	foreach (tie (name, wpa), analyses)
//	{
		// TODO: this needs more context, like whether its a class or whats its
		// params are. And the relationship to the pints-to graph.
//		wpa->init_function (cfg->method);
//	}

	Edge_list* cfg_wl = new Edge_list (cfg->get_entry_edge ());

	foreach (Edge* e, *cfg->get_all_edges ())
		e->is_executable = false;

	// Process the entry blocks first (there is no edge here)
	foreach (tie (name, wpa), analyses)
	{
		wpa->visit_block (cfg->get_entry_bb ());
	}



	// 2. Stop when CFG-worklist is empty
	while (cfg_wl->size () > 0)
	{
		Edge* e = cfg_wl->front();
		cfg_wl->pop_front ();

		if (e->is_executable)
			continue;

		e->is_executable = true;

		// Analyse the block. This does not, in any case, update the block.
		// Updating is too difficult to get right, and, in some cases, provides
		// two ways to do the same thing. For example, CCP might be able to
		// update a value, but VRP must make its results available. The dichotomy
		// will be annoying. So passes visit first, and update later. Then we
		// iterate.
		//
		// The only thing that suffers from this is eval/includes, which won't
		// have the advantage of the conditional execution. Fortunately, they are
		// not likely to benefit from it hugely, unlike the other passes.
		foreach (tie (name, wpa), analyses)
		{
			wpa->visit_block (e->get_target ());
			wpa->dump ();
		}

		// Add next	block(s)
		if (Branch_block* branch = dynamic_cast<Branch_block*> (e->get_target ()))
		{
			cfg_wl->push_back_all (get_branch_successors (branch));
		}
		else
			cfg_wl->push_back (e->get_target ()->get_successor_edges ()->front ());
	}


	// Apply the results
	foreach (Basic_block* bb, *cfg->get_all_bbs())
	{
		foreach (tie (name, wpa), analyses)
		{
			// TODO: apply results from analyses
		}
	}

	// TODO: To iterate, we would need to clone the results. But since we are
	// annotating every program point with a copy of the results, its grand
	// really.
}

Edge_list*
Whole_program::get_branch_successors (Branch_block* bb)
{
	WPA* wpa;
	string name;

	Edge_list* result = new Edge_list;

	bool known_true = false;
	bool known_false = false;
	foreach (tie (name, wpa), analyses)
	{
		if (wpa->branch_is_true (bb->branch))
			known_true = true;
		else if (wpa->branch_is_false (bb->branch))
			known_false = true;
	}

	assert (!(known_false && known_true));
	if (!known_false)
		result->push_back (bb->get_true_successor_edge ());
	if (!known_true)
		result->push_back (bb->get_false_successor_edge ());

	return result;
}

void
Whole_program::register_analysis (string name, WPA* analysis)
{
	assert (!analyses.has (name));
	analyses[name] = analysis;
}

Method_info_list*
Whole_program::get_possible_receivers (Method_invocation* in)
{
	Method_info_list* result = new Method_info_list;

	// If there is a target or a variable_method, there may be > 1 methods that
	// match it.
	if (in->target)
		phc_TODO ();

	if (isa<Variable_method> (in->method_name))
		phc_TODO ();

	String* name = dyc<METHOD_NAME> (in->method_name)->value;

	// This assumes there is only 1 function of that name, which is true. If
	// there are multiple versions, they are lowered to different names before
	// MIR.
	Method_info* info = Oracle::get_method_info (name);
	if (info == NULL)
		phc_TODO ();

	result->push_back (info);

	return result;	
}

void
Whole_program::invoke_method (Method_invocation* in)
{
	Method_info_list* receivers = get_possible_receivers (in);

	// Need to clone the information and merge it when it returns.
	if (receivers->size () > 1)
		phc_TODO ();

	foreach (Method_info* receiver, *receivers)
	{
		evaluate_method_info (receiver);
	}
}

void
Whole_program::evaluate_method_info (Method_info* info)
{
	if (info->has_implementation ())
	{
		if (info->has_parameters ())
			phc_TODO ();

		evaluate_function (new CFG (info->implementation));
	}
	else
	{
		// Get as precise information as is possible with pre-baked summary
		// information.
		evaluate_summary (info);
	}
}

void
Whole_program::evaluate_summary (Method_info* info)
{
	WPA* wpa;
	string name;

	foreach (tie (name, wpa), analyses)
	{
		wpa->use_summary_results (info);
	}
}
