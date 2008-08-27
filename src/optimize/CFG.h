/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Control-flow Graph
 */

#ifndef PHC_CFG
#define PHC_CFG

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/logic/tribool.hpp>

#include "lib/List.h"


class Basic_block;
typedef List<Basic_block*> BB_list;
class Dominance;
class Phi;
class Branch_block;

/* Add a property for Basic blocks */
enum vertex_bb_t { vertex_bb };

/* Property for branch direction */
enum edge_branch_direction_t { edge_branch_direction };

// TODO: Remove. If phc is being used as a library, this isn't very polite,
// and could lead to the same problems as monkey-patching in Ruby. 
namespace boost {
  BOOST_INSTALL_PROPERTY(vertex, bb);
  BOOST_INSTALL_PROPERTY(edge, branch_direction);
}

typedef boost::adjacency_list<
	boost::listS,
	boost::listS,
	boost::bidirectionalS, // we want access to source and targets of edges

	// Vertex properties
	boost::property<boost::vertex_index_t, int,
		boost::property<boost::vertex_color_t, boost::default_color_type,
			boost::property <vertex_bb_t, Basic_block*> > >,

	// Edge property
	boost::property<edge_branch_direction_t, boost::logic::tribool>
> Graph;


// Vertex and Edge types
typedef Graph::vertex_descriptor vertex_t;
typedef Graph::edge_descriptor edge_t;



class CFG;
#include "Basic_block.h"
#include "SSA.h"
#include "MIR.h"

/* Boost::Graph is a nice library for graphs, but a little difficult to use,
 * so we don't use it directly. */
class CFG
{
public:
	/*
	 * Boost::Graph properties
	 */

	// Accessor for BB property. Access using vb[vertex].
	boost::property_map<Graph, vertex_bb_t>::type vb;

	// Get color map
	boost::property_map<Graph, vertex_color_t>::type cm;

	// Accessor for Edge direction property. Access using ebd[edge].
	boost::property_map<Graph, edge_branch_direction_t>::type ebd;

	// Accessor for index property. Access using index[vertex] (this is here
	// for graphviz, so it should be rare to require access to it.
	boost::property_map<Graph, boost::vertex_index_t>::type index;

public:
	/*
	 * CFG creation and manipulation
	 */

	CFG (MIR::Method* method);
	List<MIR::Statement*>* get_linear_statements ();

	// Add the BB to the graph, and update the BB's vertex.
	vertex_t add_bb (Basic_block* bb);
	edge_t add_edge (Basic_block* source, Basic_block* target);
	std::pair<edge_t, edge_t> add_branch (
		Branch_block* source, 
		Basic_block* target1, 
		Basic_block* target2);

public:
	void dump_graphviz (String* label);

public:
	/*
	 * CFG access
	 */
	Basic_block* get_entry_bb ();
	Basic_block* get_exit_bb ();

	BB_list* get_all_bbs ();
	BB_list* get_all_bbs_top_down ();
	BB_list* get_all_bbs_bottom_up ();

public:
	/*
	 * SSA information
	 */
	Dominance* dominance;
	friend class Dominance;
	friend class Basic_block;
	friend class Branch_block;

private:
	Graph bs; // backing store

	friend struct filter_back_edges;

	MIR::Method* method;
	vertex_t entry;
	vertex_t exit;

	void add_statements (MIR::Statement_list*);
	void convert_to_ssa_form ();
	BB_list* get_bb_successors (Basic_block* bb);
	BB_list* get_bb_predecessors (Basic_block* bb);
	edge_t get_edge (Basic_block* bb1, Basic_block* bb2);

	/* returns true or false. If edge isnt true or false, asserts. */
	bool is_true_edge (edge_t edge);

	// If we use a graph with listS for the adjacency lists, then we need to
	// renumber the indices for certain algorithms.
	void renumber_vertex_indices ();
	void consistency_check ();
};

#endif // PHC_CFG
