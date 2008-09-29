
#include <boost/foreach.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/dominator_tree.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/transpose_graph.hpp>
#include <boost/graph/reverse_graph.hpp>
#include <boost/graph/topological_sort.hpp>

#include "process_ir/General.h"

#include "SSA.h"
#include "Phi.h"

using namespace MIR;
using namespace boost;

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
 *	Reverse Dominator:
 *	Reverse Immediate Dominator:
 *	Reverse Dominaance Frontier:
 *		Same thing on a reversed CFG.
 *
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
Dominance::calculate_forward_dominance()
{
	calculate_dominance (cfg->bs, cfg->entry);
}

void
Dominance::calculate_reverse_dominance ()
{
	// TODO: reverse graph gives the wrong type, but is O(1)
	Graph transposed;
	transpose_graph (cfg->bs, transposed);

	reverse_dominance = new Dominance (cfg);
	reverse_dominance->calculate_dominance (transposed, cfg->exit);
}


void
Dominance::calculate_dominance (Graph& graph, vertex_t entry)
{
	// Use this function for both dominance and reverse dominance, so don't use
	// BB properties and methods. CFG's vertices must map to GRAPH's vertices
	// using cfg->vb, we can use CFG properties though, so long as they dont
	// specify a direction.


	// Step 1: Calculate immediate dominators.
	// This automatically builds dominators: ie, given y, find x such
	// that x idom y.
	// From HERE to THERE copied straight from boost documentation.
	typedef property_map<Graph, vertex_index_t>::type IndexMap;
	typedef iterator_property_map<vector<vertex_t>::iterator, IndexMap> PredMap;
	cfg->renumber_vertex_indices ();	
	vector<vertex_t> domTreePredVector = vector<vertex_t> (
		num_vertices (graph),
		graph_traits<Graph>::null_vertex());
	PredMap idom_calc = make_iterator_property_map (
		domTreePredVector.begin (),
		get(vertex_index, graph));
	lengauer_tarjan_dominator_tree(graph, entry, idom_calc);
	foreach (vertex_t v, vertices (graph))
	{
		if (get(idom_calc, v) != graph_traits<Graph>::null_vertex())
			idominator[v] = get(idom_calc, v);
		else
			idominator[v] = NULL;
	}

	// THERE (see HERE)

	// Build forward dominators
	// We also want to find the block that are immedately dominated by
	// another block (ie [a,b,c] such that x idom a, x idom b and x idom c.

	foreach (vertex_t v, vertices (graph))
	{
		// ENTRY and any unreachable nodes may have no immediate dominator.
		vertex_t dom = idominator[v];
		if (dom != NULL)
			idominated [dom].push_back (v);
	}


	/* Use the function in Cooper/Torczon, Figure 9.10 */
	foreach (vertex_t n, vertices (graph))
	{
		if (in_degree (n, graph) > 0)
		{
			foreach (edge_t e, in_edges (n, graph))
			{
				vertex_t runner = source (e, graph);
				// Dont include RUNNER, since it dominates itself.
				while (runner != idominator[n] && runner != n)
				{
					// TODO: do in linear-time
					bool is_already_in_df = false;
					foreach (vertex_t frontier, df[runner])
						if (frontier == n)
							is_already_in_df = true;

					if (!is_already_in_df)
						df [runner].push_back (n);

					runner = idominator[runner];
				}
			}
		}
	}
}

void
Dominance::dump ()
{
	CHECK_DEBUG ();

	foreach (vertex_t v, vertices (cfg->bs))
	{
		cfg->vb[v]->dump();
		cdebug << " - dominates (forward_idom): [";
		foreach (vertex_t dominated, idominated[v])
		{
			cfg->vb[dominated]->dump();
			cdebug << ", ";
		}
		cdebug << "]\n\n";

		cdebug << " - is dominated by (idom): ";
		if (idominator[v] == NULL)
			cdebug << "NONE";
		else
			cfg->vb[idominator[v]]->dump();
		cdebug << "\n\n";

		cdebug << " - dominance frontier: [";
		foreach (vertex_t frontier, df[v])
		{
			cfg->vb[frontier]->dump();
			cdebug << ", ";
		}
		cdebug << "]\n\n";
	}
}

BB_list*
Dominance::get_bb_dominance_frontier (Basic_block* bb)
{
	BB_list* result = new BB_list;
	foreach (vertex_t v, df [bb->vertex])
		result->push_back (cfg->vb[v]);

	return result;
}

Basic_block*
Dominance::get_bb_immediate_dominator (Basic_block* bb)
{
	return cfg->vb [idominator [bb->vertex]];
}


BB_list*
Dominance::get_blocks_dominated_by_bb (Basic_block* bb)
{
	BB_list* result = new BB_list;
	foreach (vertex_t v, idominated [bb->vertex])
		result->push_back (cfg->vb [v]);

	return result;
}

bool
Dominance::is_bb_dominated_by (Basic_block* bb, Basic_block* potential_dom)
{
	vertex_t v = bb->vertex;
	// Go up the dominator chain
	while (idominator[v] != NULL)
	{
		if (idominator[v] == potential_dom->vertex)
			return true;
		else
			v = idominator[v];
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

	// Convert the phi nodes
	foreach (VARIABLE_NAME* phi_lhs, *bb->get_phi_lhss())
	{
		DEBUG ("converting phi lhs");
		debug (phi_lhs);
//		create_new_ssa_name (phi_lhs);

		VARIABLE_NAME* clone = phi_lhs->clone ();
		create_new_ssa_name (clone);
		bb->update_phi_node (phi_lhs, clone);

		DEBUG (" to ");
		debug (phi_lhs);
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
		DEBUG ("Converting def " << *def->get_ssa_var_name ());
		debug (def);
		create_new_ssa_name (def);
		DEBUG (" to ");
		debug (def);
	}

	// Copy names to CFG successors (including names defined in
	// predecessor, which are not redefined here).
	foreach (Basic_block* succ, *bb->get_successors ())
		foreach (VARIABLE_NAME* phi_lhs, *succ->get_phi_lhss())
			succ->add_phi_arg (phi_lhs, read_var_stack (phi_lhs), cfg->get_edge (bb, succ));


	// Recurse down the dominator tree
	foreach (Basic_block* dominated, *bb->get_dominated_blocks ())
		rename_vars (dominated);


	// Before going back up the tree, get rid of new variable names from
	// the stack, so the next node up sees its own names.
	foreach (VARIABLE_NAME* def, *bb->get_pre_ssa_defs ())
		pop_var_stack (def);
}
