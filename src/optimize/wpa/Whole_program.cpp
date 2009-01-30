/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Perform a number of whole-program analyses simulteneously.
 *
 * Design of the whole-program optimizer
 *
 *		1. Perform flow-sensitive, context-sensitive analysis. When analysing a
 *		function in multiple contexts, clone the function, and store the clones
 *		in the call-graph. 
 *
 *		2. Before analysing each Basic_block, clear all phc.opt.* annotations.
 *		After analysing each block, each analysis re-annotates the block. At
 *		function-exit, the annotations stay.
 *
 *
 *		3. The analyses data structures' are cloned at split nodes, and
 *		combined at join nodes, whereupon the analysis proceeds for a single
 *		iteration.
 *
 *		4. After the analysis is complete, all the function annotations can be
 *		merged.
 *
 *		5. Once merged, the analyses are re-run over the complete call-graph,
 *		transforming the graph. This iterates until it converges (or a fixed
 *		number of times). This allows evals and includes to be replaced with
 *		their respective code.
 *
 *		6. Once finished, the combined alias-solution is used to annotate the
 *		results for SSA, where-upon DCE is run over the entire program.
 *
 *		7. Finally, code is generated using the (hopefully) well-annotated
 *		code.
 */

#include "process_ir/General.h"

#include "optimize/Edge.h"
#include "optimize/Oracle.h"

#include "Aliasing.h"
#include "Callgraph.h"
#include "CCP.h"
#include "Constant_state.h"
#include "Def_use.h"
#include "Include_analysis.h"
#include "pass_manager/Pass_manager.h"
#include "Type_inference.h"
#include "VRP.h"
#include "Whole_program.h"
#include "WPA.h"

using namespace MIR;
using namespace boost;

Whole_program::Whole_program (Pass_manager* pm)
: pm (pm)
{
	// First class citizens:
	//		- Aliasing stores the analysis results, and passes them to the
	//		second-class citizens
	//		- Callgraph has a yet unrealized purpose.
	//		- CCP helps resolve branches
	aliasing = new Aliasing (this);
	callgraph = new Callgraph (this);
	ccp = new CCP (this);

	// Second class citizens
	//		- These consume data created by the first-class citizens.

	def_use = new Def_use (this);
//	constant_state = new Constant_state (this);
//	include_analysis = new Include_analysis (this);
//	vrp = new VRP (this);


	register_analysis ("Callgraph", callgraph);
	register_analysis ("CCP", ccp);
	register_analysis ("Def-use", def_use);
//	register_analysis ("Constant_state", constant_state);
//	register_analysis ("Include_analysis", include_analysis);
//	register_analysis ("Type_inference", new Type_inference (this));
//	register_analysis ("VRP", vrp);
}

void
Whole_program::run (MIR::PHP_script* in)
{
	invoke_method (
		new Method_invocation (
			NULL,
			new METHOD_NAME (s("__MAIN__")),
			new Actual_parameter_list),
		NULL,
		NULL);


	foreach (String* method, *callgraph->get_called_methods ())
	{
		Method_info* info = Oracle::get_method_info (method);

		if (!info->has_implementation ())
			continue;

		// Merge different contexts
		merge_contexts (info);

		// Generate Method_infos from the analysis results
		generate_summary (info);
	}

	// TODO: some kind of iteration. apply_results would be better if the
	// full points-to analysis was recalculated after
	// perform_local_optimizations.
	
	foreach (String* method, *callgraph->bottom_up ())
	{
		Method_info* info = Oracle::get_method_info (method);

		if (!info->has_implementation ())
			continue;

		// Apply the results
		apply_results (Oracle::get_method_info (method));

		// TODO: we need to redo alias analysis here to get more precise results.
		// Perform DCE and CP.
		perform_local_optimizations (info);

		// Perform inlining
		// TODO:
	}
}


void
Whole_program::analyse_function (Basic_block* context, CFG* cfg, MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* lhs)
{
	// This is very similar to run() from Sparse_conditional_visitor, except
	// that it isnt sparse.

	WPA* wpa;
	string name;

	cfg->dump_graphviz (NULL);

	// 1. Initialize:
	Edge_list* cfg_wl = new Edge_list (cfg->get_entry_edge ());

	foreach (Edge* e, *cfg->get_all_edges ())
		e->is_executable = false;

	// Process the entry blocks first (there is no edge here)
	DEBUG ("Initing functions");
	aliasing->forward_bind (context, cfg, actuals, lhs);


	// 2. Stop when CFG-worklist is empty
	while (cfg_wl->size () > 0)
	{
		Edge* e = cfg_wl->front();
		cfg_wl->pop_front ();


		// Analyse the block, storing per-basic-block results.
		// This does not update the block structure.

		bool changed = aliasing->analyse_block (e->get_target ());

		// Always pass through at least once.
		if (e->is_executable == false)
			changed = true;

		// Tell successors that we are executable.
		e->is_executable = true;

		// Add next	block(s)
		if (changed)
		{
			if (Branch_block* branch = dynamic_cast<Branch_block*> (e->get_target ()))
				cfg_wl->push_back_all (get_branch_successors (branch));
			else if (!isa<Exit_block> (e->get_target ()))
				cfg_wl->push_back (e->get_target ()->get_successor_edges ()->front ());
		}
	}

	aliasing->backward_bind (context, cfg);
}

Edge_list*
Whole_program::get_branch_successors (Branch_block* bb)
{
	Edge_list* result = new Edge_list;

	if (!ccp->branch_is_true (bb->branch))
		result->push_back (bb->get_false_successor_edge ());

	if (!ccp->branch_is_false (bb->branch))
		result->push_back (bb->get_true_successor_edge ());

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
Whole_program::invoke_method (Method_invocation* in, Basic_block* context, MIR::VARIABLE_NAME* lhs)
{
	Method_info_list* receivers = get_possible_receivers (in);

	// Need to clone the information and merge it when it returns.
	if (receivers->size () > 1)
		phc_TODO ();

	
	foreach (Method_info* receiver, *receivers)
	{
		// TODO: where should I clone the actuals?
		analyse_method_info (receiver, context, in->actual_parameters, lhs);
	}
}

void
Whole_program::analyse_method_info (Method_info* info,
												Basic_block* context,
												MIR::Actual_parameter_list* actuals,
												MIR::VARIABLE_NAME* lhs)
{
	if (info->has_implementation ())
		analyse_function (context, info->cfg, actuals, lhs);
	else
	{
		if (lhs)
			phc_TODO ();

		// Get as precise information as is possible with pre-baked summary
		// information.
		analyse_summary (info, context, actuals, lhs);
	}
}

void
Whole_program::analyse_summary (Method_info* info, Basic_block* context, Actual_parameter_list* actuals, VARIABLE_NAME* lhs)
{
	WPA* wpa;
	string name;

	// TODO: We'll pretend for now that these have the same length. We should
	// probably have a final Parameter_info which models the remaining
	// actuals, with pass_by_ref etc (which is a bit different than the
	// current Oracle solution of is_param_x_pass_by_ref).
	if (info->params->size () != actuals->size ())
		phc_TODO ();

	foreach (tie (name, wpa), analyses)
		aliasing->use_summary_results (context, info, actuals, lhs);
}

void
Whole_program::apply_results (Method_info* info)
{
	if (!info->has_implementation ())
		return;

	foreach (Basic_block* bb, *info->cfg->get_all_bbs ())
	{
		// We apply all results through aliasing. Its the only place we have all
		// the information we need (ie is this type weird, is it making an
		// implicit call, can we actually replace $x with its value, etc. Since
		// we need this information for tons of differernt optimizations, its
		// best to have a single transformer applying the results.
		//
		// Additionally, the results are indexed by the name the Points-to
		// analyser gives them, so we need acceess to this while these
		// transformations are running.
		aliasing->apply_results (bb);
	}
	info->cfg->dump_graphviz (s("Apply results"));
}

void
Whole_program::perform_local_optimizations (Method_info* info)
{
	if (info->has_implementation ())
		pm->run_local_optimization_passes (info->cfg);
}

void
Whole_program::generate_summary (Method_info* info)
{
	// it already has a summary
	if (!info->has_implementation ())
		return;

	// TODO
//	phc_TODO ();
}

void
Whole_program::merge_contexts (Method_info* info)
{
	// TODO: once we have a function that's called from multiple different
	// places.
}


