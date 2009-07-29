
#include <algorithm>
#include <boost/graph/dominator_tree.hpp>
#include <boost/graph/reverse_graph.hpp>

#include "process_ir/General.h"
#include "lib/Vector.h"

#include "optimize/Basic_block.h"
#include "Dominance.h"

using namespace MIR;
using namespace std;
using namespace boost;

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
 *	We need to calculate the dominance frontier. Although a linear-time
 *	algorithm exists (see Muchnick), its much easier to use Cooper/Torczons
 *	iterative algorithm.
 */

Dominance::Dominance (CFG* cfg)
: cfg(cfg)
{
	// Keep the calls to calculate the dominance information out of here.
	// Since the dominance needs to be used while its still incomplete, we
	// have to access it (which we do via the CFG) before cfg->dominance has
	// been assigned.
}

template<class Graph_type>
void
calculate_dominance (Dominance* info, Graph_type& graph, vertex_t entry)
{
	// Use this function for both dominance and reverse dominance, so don't use
	// BB properties and methods. CFG's vertices must map to GRAPH's vertices
	// using cfg->vb, we can use CFG properties though, so long as they dont
	// specify a direction.

	// Calculating info->idominator is copied, with very few changes, from
	// Boost documentation.


	// Step 1: Calculate immediate dominators.
	// This automatically builds dominators: ie, given y, find x such
	// that x idom y.
	typedef typename property_map<Graph_type, vertex_index_t>::type IndexMap;
	typedef iterator_property_map<Vector<vertex_t>::iterator, IndexMap> PredMap;
	info->cfg->renumber_vertex_indices ();	
	Vector<vertex_t> domTreePredVector = Vector<vertex_t> (
		num_vertices (graph),
		graph_traits<Graph_type>::null_vertex ());

	// Use new instance, because the reverse_map<Graph> one is read-only.
	IndexMap indices; 
	PredMap idom_calc = make_iterator_property_map (
		domTreePredVector.begin (),
		indices);

	lengauer_tarjan_dominator_tree(graph, entry, idom_calc);
	foreach (vertex_t v, vertices (graph))
	{
		if (get(idom_calc, v) != graph_traits<Graph_type>::null_vertex ())
			info->idominator[v] = get(idom_calc, v);
		else
			info->idominator[v] = NULL;
	}


	// Build forward dominators
	// We also want to find the block that are immedately dominated by
	// another block (ie [a,b,c] such that x idom a, x idom b and x idom c.
	foreach (vertex_t v, vertices (graph))
	{
		// ENTRY and any unreachable nodes may have no immediate dominator.
		vertex_t dom = info->idominator[v];
		if (dom != NULL)
			info->idominated [dom].push_back (v);
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
				while (runner != info->idominator[n] && runner != n)
				{
					// TODO: do in linear-time
					bool is_already_in_df = false;
					foreach (vertex_t frontier, info->df[runner])
						if (frontier == n)
							is_already_in_df = true;

					if (!is_already_in_df)
						info->df [runner].push_back (n);

					runner = info->idominator[runner];
				}
			}
		}
	}
}

void
Dominance::calculate_forward_dominance()
{
	calculate_dominance (this, cfg->bs, cfg->entry);
}

// TODO: This fails if there is an infinite loop, so make a pretend edge to the
// exit block.
void
Dominance::calculate_reverse_dominance ()
{
	if (cfg->exit == NULL)
		reverse_dominance = NULL;
	else
	{
		// reverse_graph<Graph> is not related to Graph, so we must use
		// templates for caluclate dominance (meaning it cannot be a method).
		reverse_dominance = new Dominance (cfg);
		reverse_graph<Graph> rev (cfg->bs);
		calculate_dominance (reverse_dominance, rev, cfg->exit);
	}
}


void
Dominance::dump ()
{
	CHECK_DEBUG ();

	foreach (vertex_t v, vertices (cfg->bs))
	{
		cfg->vb[v]->dump ();
		cdebug << " - dominates (forward_idom): [";
		foreach (vertex_t dominated, idominated[v])
		{
			cfg->vb[dominated]->dump ();
			cdebug << ", ";
		}
		cdebug << "]\n\n";

		cdebug << " - is dominated by (idom): ";
		if (idominator[v] == NULL)
			cdebug << "NONE";
		else
			cfg->vb[idominator[v]]->dump ();
		cdebug << "\n\n";

		cdebug << " - dominance frontier: [";
		foreach (vertex_t frontier, df[v])
		{
			cfg->vb[frontier]->dump ();
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
	return is_bb_strictly_dominated_by (bb, potential_dom) || bb == potential_dom;
}
bool
Dominance::is_bb_strictly_dominated_by (Basic_block* bb, Basic_block* potential_dom)
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
