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
class Branch_block;
class Entry_block;
class Exit_block;
typedef List<Basic_block*> BB_list;

class Edge;
typedef List<Edge*> Edge_list;

class Dominance;
class Def_use_web;

// Property for BB*
enum vertex_bb_t { vertex_bb };

// Property for Edge*
enum edge_cfg_edge_t { edge_cfg_edge };

// TODO: Remove. If phc is being used as a library, this isn't very polite,
// and could lead to the same problems as monkey-patching in Ruby. 
namespace boost {
  BOOST_INSTALL_PROPERTY(vertex, bb);
  BOOST_INSTALL_PROPERTY(edge, cfg_edge);
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
	boost::property<edge_cfg_edge_t, Edge*>
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

	/* In general, theres no need to use properties because we have an Edge and
	 * a Basic_block class. */

	// Accessor for BB property. Access using vb[vertex]. (vb == vertex->block)
	boost::property_map<Graph, vertex_bb_t>::type vb;

	// ee = (BGL) edge -> (CFG) edge
	boost::property_map<Graph, edge_cfg_edge_t>::type ee;

	// Get color map
	boost::property_map<Graph, vertex_color_t>::type cm;

	// Accessor for index property. Access using index[vertex] (this is here
	// for graphviz, so it should be rare to require access to it.
	boost::property_map<Graph, boost::vertex_index_t>::type index;

public:
	/*
	 * CFG creation and manipulation
	 */

	// Creates a CFG for the method.
	CFG (MIR::Method* method);

	// Return a CFG for the backing store.
	CFG (Graph& bs);

	// Return a linear list of statement for the CFG
	MIR::Statement_list* get_linear_statements ();

	// This CFG should be treated as read-only, as its backing store is simply a
	// view over this bs.
	CFG* reverse ();


	void remove_unreachable_nodes ();

	// Add the BB to the graph, and update the BB's vertex.
	vertex_t add_bb (Basic_block* bb);

	Edge* add_edge (Basic_block* source, Basic_block* target);
	pair<Edge*, Edge*> add_branch (
		Branch_block* source, 
		Basic_block* target1, 
		Basic_block* target2);

private:
	void add_statements (MIR::Statement_list*);

	friend class Basic_block;
	friend class Branch_block;
	friend class Edge;

	// Insert a predecessor, fix up the neighbours. After this, BB will have a
	// single predecessor, NEW_BB, whose predecessors are BB's former
	// predecessors.
	void insert_predecessor_bb (Basic_block* bb, Basic_block* new_bb);

	// Replace EDGE with an edge from EDGE->source to NEW_BB, and an edge from
	// NEW_BB to EDGE->TARGET.
	void insert_bb_between (Edge* edge, Basic_block* new_bb);


	// Remove the basic block and fix up the neighbours.
	void remove_bb (Basic_block* bb);

	// Wrapper-interface to a number of transformations:
	//		- remove the node
	//		- replace the node
	//		- add a number of predecessor or successor nodes, in a straight line.
	// Some things arent possible:
	//		- replace branch nodes
	//		- add a node on a particular edge
	void replace_bb (Basic_block* bb, BB_list* replacements);

	// Remove the edge, and fix up the nodes.
	void remove_edge (Edge* edge);

	/* Returns true or false. If edge isnt true or false, asserts. */
	bool is_true_edge (Edge* edge);


	/* 
	 * Misc
	 */
public:
	void dump_graphviz (String* label);

	// If we use a graph with listS for the adjacency lists, then we need to
	// renumber the indices for certain algorithms.
	void renumber_vertex_indices ();

	// Remove unreachable nodes, and empty nodes.
	void tidy_up ();

	// Check that the BB->vertex mapping is symmetric.
	void consistency_check ();

public:
	/*
	 * CFG access
	 */
	Entry_block* get_entry_bb ();
	Exit_block* get_exit_bb ();

	BB_list* get_all_bbs ();
	BB_list* get_all_bbs_top_down ();
	BB_list* get_all_bbs_bottom_up ();

	Edge* get_entry_edge ();
	Edge* get_exit_edge ();
	Edge_list* get_all_edges ();
	Edge* get_edge (Basic_block* bb1, Basic_block* bb2);

private:

	// For BB methods
	BB_list* get_bb_successors (Basic_block* bb);
	BB_list* get_bb_predecessors (Basic_block* bb);
	Edge_list* get_edge_successors (Basic_block* bb);
	Edge_list* get_edge_predecessors (Basic_block* bb);


public:
	/*
	 * SSA information
	 */
	Dominance* dominance;
	friend class Dominance;

	void convert_to_ssa_form ();
	void convert_out_of_ssa_form ();
	void rebuild_ssa_form ();

	Def_use_web* duw;

private:
	Graph bs; // backing store

	friend struct filter_back_edges;

	MIR::Method* method;
	vertex_t entry;
	vertex_t exit;

};

#endif // PHC_CFG
