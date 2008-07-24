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


class Basic_block;

/* Add a property for Basic blocks */
enum vertex_bb_t { vertex_bb };

// TODO: Remove. If phc is being used as a library, this isn't very polite,
// and could lead to the same problems as monkey-patching in Ruby. 
namespace boost {
  BOOST_INSTALL_PROPERTY(vertex, bb);
}
typedef boost::property<vertex_bb_t, Basic_block*> BB;

// Graph Internal properties
typedef boost::property<
	boost::vertex_index_t, int,	// required for write_graphwiz
	BB										// make Basic_block an internal property
> Vertex_property;

typedef boost::adjacency_list<
	boost::listS,
	boost::vecS,
	boost::bidirectionalS, // we want access to source and targets of edges
	Vertex_property
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

public:

	CFG ();
	void add_statements (List<MIR::Statement*>* statements);

	// Add the BB to the graph, and update the BB's vertex.
	vertex_t add_bb (Basic_block* bb);

public:
	void dump_graphviz ();
	void consistency_check ();

public:
	Basic_block* get_entry_bb ();
	Basic_block* get_exit_bb ();

	// TODO: this will get slow. Instead we should return an iterator.
	list<Basic_block*>* get_all_bbs ();
	list<Basic_block*>* get_predecessors (Basic_block*);
	list<Basic_block*>* get_successors (Basic_block*);

private:
	Graph bs; // backing store
	vertex_t entry;
	vertex_t exit;
};

#endif // PHC_CFG
