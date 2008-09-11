
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
	args = new list<pair<MIR::VARIABLE_NAME*, Edge*> >;
}

void
Phi::add_arg (int version, Edge* edge)
{
	VARIABLE_NAME* param = lhs->clone ();
	param->set_version (version);
	args->push_back (make_pair (param, edge));
}

VARIABLE_NAME_list* 
Phi::get_args ()
{
	VARIABLE_NAME_list* result = new VARIABLE_NAME_list;
	pair<VARIABLE_NAME*, Edge*> pair;
	foreach (pair, *args)
	{
		result->push_back (pair.first);
	}
	return result;
}

list<pair<MIR::VARIABLE_NAME*, Edge*> >*
Phi::get_arg_edges ()
{
	return args;
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
 *	We need to calculate the dominace frontier. There is a linear-time
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
}

void
Dominance::calculate_immediate_dominators ()
{
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
	DEBUG ("Entry is: " << cfg->get_entry_bb ());
	DEBUG ("Exit is: " << cfg->get_exit_bb ());
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		if (get(idom_calc, bb->vertex) != graph_traits<Graph>::null_vertex())
		{
			idoms[bb] = cfg->vb[get(idom_calc, bb->vertex)];
			DEBUG ("BB " << bb << "(" << bb->get_index() << ") is dominated by " << idoms[bb]->get_index ());
		}
		else
			DEBUG ("BB: " << bb << "(" << bb->get_index() << ") does not have an immediate dominator");
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
		if (y != cfg->get_entry_bb ())
		{
			Basic_block* dom = y->get_immediate_dominator ();
			forward_idoms [dom]->push_back (y);
		}
	}
}

void
Dominance::calculate_local_dominance_frontier ()
{
	foreach (Basic_block* x, *cfg->get_all_bbs ())
	{
		// Step 2: Calculate local dominance frontier:
		//	DF_local (x) = { y in succ (x) | idom (y) != x }
		foreach (Basic_block* y, *x->get_successors ())
		{
			if (y->get_immediate_dominator () != x)
				x->add_to_dominance_frontier (y);
		}
	}
}

void
Dominance::propagate_dominance_frontier_upwards ()
{
	// Step 3: Propagate local dominance frontier upwards.
	// DF_up (x,z)  = { y in DF (z) | idom (z) = x && idom (y) != x }
	foreach (Basic_block* z, *cfg->get_all_bbs_bottom_up ())
	{
		foreach (Basic_block* x, *z->get_predecessors ())
		{
			foreach (Basic_block* y, *z->get_dominance_frontier ())
			{
				if (y->get_immediate_dominator () != x)
					x->add_to_dominance_frontier (y);
			}
		}
	}
}

void
Dominance::add_to_bb_dominance_frontier (Basic_block* bb, Basic_block* frontier)
{
	df [bb]->push_back (frontier);
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
		DEBUG ("Converting use " << use);
		debug (use);
		use->convert_to_ssa_name (read_var_stack (use));
		DEBUG (" to ");
		debug (use);
	}

	// Create new names for defs
	foreach (VARIABLE_NAME* def, *bb->get_pre_ssa_defs ())
	{
		DEBUG ("Converting def " << def);
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
