/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Points-to graph.
 *
 * There should be multiple graphs, 1 per function. there need to be links
 * between them, so I'm not clear if its better to have multiple regions within
 * a graph, or multiple graphs.
 *
 */

#ifndef PHC_POINTS_TO
#define PHC_POINTS_TO

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>

#include "lib/List.h"
#include "optimize/Var_map.h"
#include "lib/String.h"

// Property for Node*
enum vertex_pt_node_t { vertex_pt_node };

// Property for Edge*
enum edge_pt_edge_t { edge_pt_edge };

// So that we dont have to refactor CFG
struct phc_listS2 {};

namespace boost {

	BOOST_INSTALL_PROPERTY(vertex, pt_node);
	BOOST_INSTALL_PROPERTY(edge, pt_edge);

	// In order to use garbage collection, we have to specify the type to be a
	// List instead of an std::list. This is copied from container_gen.cpp.
	template <class ValueType>
	struct container_gen <phc_listS2, ValueType>
	{
		typedef List<ValueType> type;
	};

	template<>
	struct parallel_edge_traits<phc_listS2>
	{
		typedef allow_parallel_edge_tag type;
	};
}

class PT_node;
class PT_edge;

typedef boost::adjacency_list<

	// OutEdgeList
	phc_listS2,

	// VertexList
	phc_listS2,

	// Direction
	boost::bidirectionalS, // we want access to source and targets of edges

	// Vertex properties
	boost::property<boost::vertex_index_t, int,
		boost::property<boost::vertex_color_t, boost::default_color_type,
			boost::property<vertex_pt_node_t, PT_node*> > >,

	// Edge properties
	boost::property<edge_pt_edge_t, PT_edge*>,

	// Graph properties
	boost::no_property,

	// EdgeList
	phc_listS2
> PT_graph;

typedef PT_graph::vertex_descriptor vertex_pt;
typedef PT_graph::edge_descriptor edge_pt;

class Points_to : virtual public GC_obj
{
	PT_node* atom;
	Var_map<PT_node*> node_map;

public:
	Points_to ();

	// Accessors
	boost::property_map<PT_graph, vertex_pt_node_t>::type vn;

	// ee = (BGL) edge -> (PTG) edge
	boost::property_map<PT_graph, edge_pt_edge_t>::type ee;



	void consistency_check ();
	void dump_graphviz (String* label);

	PT_node* get_node (MIR::Expr* expr);
	PT_edge* add_edge (PT_node*, PT_node*);

private:
	void add_node (PT_node* node);


public:

	// TODO: we only need to clone for BBs with > 1 predecessor. But from
	// experience with GCC, it is very difficult to handle flow-sensitivity
	// without mutliple graphs.
	Points_to* clone();


private:
	PT_graph bs;

	friend class PT_edge;
	friend class PT_node;

};

#endif // PHC_POINTS_TO
