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
#include "MIR.h"
#include "Basic_block.h"



/* Add a property for Basic blocks */
enum vertex_bb_t { vertex_bb };

// TODO: Remove. If phc is beign used as a library, this isn't very polite,
// and could lead to the same problems as monkey-patching in Ruby. 
namespace boost {
  BOOST_INSTALL_PROPERTY(vertex, bb);
}

typedef boost::property<vertex_bb_t, Basic_block*> BB;


/* Internal properties for Graph */
typedef boost::property<
	boost::vertex_index_t, int, // required for write_graphwiz
	BB	// make BB an internal property
> Vertex_property;

typedef boost::adjacency_list<
	boost::listS,
	boost::vecS,
	boost::bidirectionalS, // we want access to source and targets of edges
	Vertex_property
> Graph;

typedef Graph::vertex_descriptor vertex_t;
typedef Graph::edge_descriptor edge_t;


/* Boost::Graph is a nice library for graphs, but a little difficult to use,
 * so we don't use it directly. */
class CFG
{
public:
	// Accessor for bb property. Access using bb[vertex].
	boost::property_map<Graph, vertex_bb_t>::type bb;
	static const int DEFAULT_SIZE = 50;

public:

	CFG ();
	void add_statements (List<MIR::Statement*>* statements);
	void add_block (MIR::Statement* statement);

public:
	void dump_graphviz ();

private:
	Graph bs; // backing store
};

#endif // PHC_CFG
