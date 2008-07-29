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


class Basic_block;
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
		boost::property <vertex_bb_t, Basic_block*> >,

	// Edge property
	boost::property<edge_branch_direction_t, boost::logic::tribool>
> Graph;


// Vertex and Edge types
typedef Graph::vertex_descriptor vertex_t;
typedef Graph::edge_descriptor edge_t;



class CFG;
#include "Basic_block.h"
#include "MIR.h"

/* Boost::Graph is a nice library for graphs, but a little difficult to use,
 * so we don't use it directly. */
class CFG
{
public:
	// Accessor for BB property. Access using vb[vertex].
	boost::property_map<Graph, vertex_bb_t>::type vb;

	// Accessor for Edge direction property. Access using ebd[edge].
	boost::property_map<Graph, edge_branch_direction_t>::type ebd;

	// Accessor for index property. Access using index[vertex] (this is here
	// for graphviz, so it should be rare to require access to it.
	boost::property_map<Graph, boost::vertex_index_t>::type index;

public:

	CFG ();
	void add_statements (List<MIR::Statement*>* statements);
	List<MIR::Statement*>* get_linear_statements ();

	// Add the BB to the graph, and update the BB's vertex.
	vertex_t add_bb (Basic_block* bb);
	edge_t add_edge (Basic_block* source, Basic_block* target);
	std::pair<edge_t, edge_t> add_branch (Branch_block* source, Basic_block* target1, Basic_block* target2);

public:
	void dump_graphviz (String* label);
	void consistency_check ();

public:
	Basic_block* get_entry_bb ();
	Basic_block* get_exit_bb ();

	// TODO: this will get slow. Instead we should return an iterator.
	list<Basic_block*>* get_all_bbs ();

	list<Basic_block*>* get_predecessors (Basic_block*);
	list<Basic_block*>* get_successors (Basic_block*);

	// Assert a block has a single successor, and return it.
	Basic_block* get_successor (Basic_block*);

	// Assert a block has a two successors, representing true and false
	// branches, and return the true branch.
	Basic_block* get_true_successor (Branch_block*);

	// Assert a block has a two successors, representing true and false
	// branches, and return the false branch.
	Basic_block* get_false_successor (Branch_block*);

	void replace_bb (Basic_block* bb, list<Basic_block*>* replacements);
	void remove_bb (Basic_block* bb);

private:
	Graph bs; // backing store
	vertex_t entry;
	vertex_t exit;

	// If we use a graph with listS for the adjacency lists, then we need to
	// renumber the indices for certain algorithms.
	void renumber_vertex_indices ();
};

#endif // PHC_CFG
