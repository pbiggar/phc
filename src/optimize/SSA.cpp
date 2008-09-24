
#include <boost/foreach.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/dominator_tree.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/topological_sort.hpp>

#include "process_ir/debug.h"

#include "SSA.h"

using namespace MIR;
using namespace boost;

Phi::Phi (VARIABLE_NAME* var_name)
: lhs(var_name)
{
	args = new list<pair<MIR::Rvalue*, Edge*> >;
}

void
Phi::add_arg (int version, Edge* edge)
{
	VARIABLE_NAME* param = lhs->clone ();
	param->set_version (version);
	args->push_back (make_pair (param, edge));
}

Rvalue_list* 
Phi::get_args ()
{
	Rvalue_list* result = new Rvalue_list;
	pair<Rvalue*, Edge*> pair;
	foreach (pair, *args)
	{
		result->push_back (pair.first);
	}
	return result;
}

list<pair<MIR::Rvalue*, Edge*> >*
Phi::get_arg_edges ()
{
	return args;
}

void
Phi::remove_arg_for_edge (Edge* edge)
{
	list<pair<MIR::Rvalue*, Edge*> >::iterator i;
	for (i = args->begin (); i != args->end (); i++)
	{
		if ((*i).second == edge)
		{
			args->erase (i);
			return;
		}
	}

	assert (0);
}


bool
Phi::has_arg_for_edge (Edge* edge)
{
	list<pair<MIR::Rvalue*, Edge*> >::iterator i;
	for (i = args->begin (); i != args->end (); i++)
		if ((*i).second == edge)
			return true;
	
	return false;
}

// Tell the phi node that OLD_EDGE is being removed, and replaced by NEW_EDGE.
void
Phi::replace_edge (Edge* old_edge, Edge* new_edge)
{
	list<pair<MIR::Rvalue*, Edge*> >::iterator i;
	for (i = args->begin (); i != args->end (); i++)
	{
		if ((*i).second == old_edge)
		{
			(*i).second = new_edge;
			return;
		}
	}

	assert (0);
}


void
Phi::replace_var_name (MIR::VARIABLE_NAME* old_var_name, MIR::Rvalue* new_rval)
{
	// We get pair copies with a foreach loop, which wont update the original.
	// Also, we can't use a reference in a foreach loop, since there is a
	// comma in the pair declaration.
	list<pair<MIR::Rvalue*, Edge*> >::iterator i;
	for (i = args->begin (); i != args->end (); i++)
	{
		if ((*i).first == old_var_name)
		{
			(*i).first = new_rval;
			return;
		}
	}

	assert (0);
}

void
Phi::dump ()
{
	DEBUG ("Phi node for " << *lhs->get_ssa_var_name ());
}


// We use Muchnick, Section 8.11 (which is essentially the same as the
// Minimal SSA form from the original Cytron, Ferrante, Rosen, Wegman and
// Zadeck paper), and Cooper/Torczon Chapter 9.

/*
 * Terms (from Muchnick 7.3)
 * 
 * Dominator:
 *		A basic block X dominates another, Y, if X must be executed before Y.
 *		X dominates X.  Technically, if all paths from ENTRY to Y must go
 *		through X.  
 *
 *	Immediate dominator:
 *		The unique dominator U of a BB X, for which there is no BB dominated by
 *		U which dominates X.
 *
 *	Strict dominator (we dont use this term yet):
 *		X sdom Y if X dom Y and X != Y.
 *
 *	Dominance Frontier:
 *		DF (X) is the set of nodes dominated by X, whose successors are not
 *		dominated by X (well, one or more are not dominated by X).
 *	
 *	We need to calculate the dominance frontier. There is a linear-time
 *	algorithm for this:
 *
 * 1) Find DF_local (X):
 *		DF_local (x) = { y in succ (x) | idom (y) != x } The set of successors
 *		of X, which are not immediately dominated by X.
 *
 *	2) Find DF_up (X, Z):
 *		DF_up (x,z)  = { y in DF (z) | idom (z) = x && idom (y) != x } We want
 *		to propagate each the dominance frontiers of Z to X, its immediate
 *		dominator, if X doesnt dominate frontier (Y).
 *
 * 3) Propagate frontier
 *		Iteratively propagate DF_local (Z) from dominated block Z to immediate
 *		dominator X via DF_up (X, Z).
 */

Dominance::Dominance (CFG* cfg)
: cfg(cfg)
{
	// Keep the calls to calculate the dominance information out of here.
	// Since the dominance needs to be used while its still incomplete, we
	// have to access it (which we do via the CFG) before cfg->dominance has
	// been assigned.
}

void
Dominance::calculate_immediate_dominators ()
{
	// Step 0: Remove unreachable nodes. Everything should be reachable from the
	// entry block, or it wont dominate everything.
	cfg ->tidy_up ();

	// Step 1: Calculate immediate dominators.

	// This automatically builds reverse dominators, ie, given y, find x such
	// that x idom y.
	// From HERE to THERE copied straight from boost documentation.
	typedef property_map<Graph, vertex_index_t>::type IndexMap;
	typedef iterator_property_map<vector<vertex_t>::iterator, IndexMap> PredMap;
	cfg->renumber_vertex_indices ();	
	vector<vertex_t> domTreePredVector = vector<vertex_t>(
		num_vertices(cfg->bs),
		graph_traits<Graph>::null_vertex());
	PredMap idom_calc = make_iterator_property_map(
		domTreePredVector.begin(),
		get(vertex_index, cfg->bs));
	lengauer_tarjan_dominator_tree(cfg->bs, cfg->entry, idom_calc);
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		if (get(idom_calc, bb->vertex) != graph_traits<Graph>::null_vertex())
			idoms[bb] = cfg->vb[get(idom_calc, bb->vertex)];
		else
			idoms[bb] = NULL;
	}

	// THERE (see HERE)

	// Build forward dominators
	// We also want to find the block that are immedately dominated by
	// another block (ie [a,b,c] such that x idom a, x idom b and x idom c.

	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		forward_idoms[bb] = new BB_list;
		df[bb] = new BB_list;
	}

	foreach (Basic_block* y, *cfg->get_all_bbs ())
	{
		// ENTRY and any unreachable nodes may have no immediate dominator.
		Basic_block* dom = y->get_immediate_dominator ();
		if (dom != NULL)
			forward_idoms [dom]->push_back (y);
	}
}

/* Use the function in Cooper/Torczon, Figure 9.10 */
void
Dominance::calculate_dominance_frontier ()
{
	foreach (Basic_block* n, *cfg->get_all_bbs ())
	{
		BB_list* preds = n->get_predecessors ();
		if (preds->size() > 0)
		{
			foreach (Basic_block* pred, *preds)
			{
				Basic_block* runner = pred;
				// Dont include RUNNER, since it dominates itself.
				while (runner != idoms[n] && runner != n)
				{
					runner->add_to_dominance_frontier (n);
					runner = idoms[runner];
				}
			}
		}
	}
}

void
Dominance::dump ()
{
	CHECK_DEBUG ();

	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		bb->dump();
		cdebug << " - dominates (forward_idom): [";
		foreach (Basic_block* dominated, *forward_idoms[bb])
		{
			dominated->dump();
			cdebug << ", ";
		}
		cdebug << "]\n\n";

		cdebug << " - is dominated by (idom): ";
		if (idoms[bb] == NULL)
			cdebug << "NONE";
		else
			idoms[bb]->dump();
		cdebug << "\n\n";

		cdebug << " - dominance frontier: [";
		foreach (Basic_block* frontier, *df[bb])
		{
			frontier->dump();
			cdebug << ", ";
		}
		cdebug << "]\n\n";
	}
}

void
Dominance::add_to_bb_dominance_frontier (Basic_block* bb, Basic_block* frontier)
{
	if (!is_bb_in_dominance_frontier (bb, frontier))
		df [bb]->push_back (frontier);
}


bool
Dominance::is_bb_in_dominance_frontier (Basic_block* bb, Basic_block* frontier)
{
	// TODO this can be done in constant-time if we change the form
	foreach (Basic_block* i, *df[bb])
		if (i == frontier)
			return true;
	
	return false;
}

BB_list*
Dominance::get_bb_dominance_frontier (Basic_block* bb)
{
	return df[bb];
}

Basic_block*
Dominance::get_bb_immediate_dominator (Basic_block* bb)
{
	return idoms[bb];
}


BB_list*
Dominance::get_blocks_dominated_by_bb (Basic_block* bb)
{
	return forward_idoms[bb];
}

bool
Dominance::is_bb_dominated_by (Basic_block* bb, Basic_block* potential_dom)
{
	// Go up the dominator chain
	while (idoms[bb] != NULL)
	{
		if (idoms[bb] == potential_dom)
			return true;
		else
			bb = idoms[bb];
	}
	
	return false;
}




SSA_renaming::SSA_renaming (CFG* cfg)
: cfg(cfg)
, counter (0)
{
}

void
SSA_renaming::push_to_var_stack (VARIABLE_NAME* var_name, int version)
{
	var_stacks[*var_name->value].push (version);
}

int
SSA_renaming::read_var_stack (VARIABLE_NAME* var_name)
{
	// In traditional SSA, all variables are initialized at the start of a
	// function. Not so here (though it could be done that way).
	if (var_stacks[*var_name->value].size () == 0)
		push_to_var_stack (var_name, counter++);

	int result = var_stacks[*var_name->value].top();
	return result;
}

void
SSA_renaming::pop_var_stack (VARIABLE_NAME* var_name)
{
	var_stacks[*var_name->value].pop();
}

void 
SSA_renaming::create_new_ssa_name (VARIABLE_NAME* var_name)
{
	var_name->convert_to_ssa_name (counter);
	push_to_var_stack (var_name, counter++);
}

void
SSA_renaming::debug_var_stacks ()
{
	CHECK_DEBUG ();
	string name;
	stack<int> st;
	foreach (tie (name,st), var_stacks)
	{
		cdebug << name << ": (TOP) ";
		stack<int> copy (st);
		while (copy.size ())
		{
			cdebug << copy.top () << ", ";
			copy.pop ();
		}
		cdebug << "(BOTTOM)" << endl;
	}
}

void 
SSA_renaming::rename_vars (Basic_block* bb)
{
	DEBUG ("renaming vars in " << *bb->get_graphviz_label ());
	debug_var_stacks ();


	// Create new names for PHI targets
	foreach (Phi* phi, *bb->get_phi_nodes ())
	{
		DEBUG ("converting phi lhs");
		debug (phi->lhs);
		create_new_ssa_name (phi->lhs);
	}

	// Rename local variable uses
	foreach (VARIABLE_NAME* use, *bb->get_pre_ssa_uses ())
	{
		DEBUG ("Converting use " << *use->get_ssa_var_name ());
		debug (use);
		use->convert_to_ssa_name (read_var_stack (use));
		DEBUG (" to ");
		debug (use);
	}

	// Create new names for defs
	foreach (VARIABLE_NAME* def, *bb->get_pre_ssa_defs ())
	{
		DEBUG ("Converting use " << *def->get_ssa_var_name ());
		debug (def);
		create_new_ssa_name (def);
		DEBUG (" to ");
		debug (def);
	}

	// Copy names to CFG successors (including names defined in
	// predecessor, which are not redefined here).
	foreach (Basic_block* succ, *bb->get_successors ())
		foreach (Phi* phi, *succ->get_phi_nodes ())
			phi->add_arg (read_var_stack (phi->lhs), cfg->get_edge (bb, succ));

	// Recurse down the dominator tree
	foreach (Basic_block* dominated, *bb->get_dominated_blocks ())
		rename_vars (dominated);

	// Before going back up the tree, get rid of new variable names from
	// the stack, so the next node up sees its own names.
	foreach (VARIABLE_NAME* def, *bb->get_pre_ssa_defs ())
		pop_var_stack (def);
}
