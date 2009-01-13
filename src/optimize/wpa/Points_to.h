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
#include "lib/Set.h"
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
class Var_node;
class Atom_node;
class PT_edge;
typedef List<PT_node*> PT_node_list;
typedef List<Var_node*> Var_node_list;
typedef List<Atom_node*> Atom_node_list;
typedef List<PT_edge*> PT_edge_list;



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

	// Rather than specify each type, we can save energy and code by
	// templatizing.
	template<class T>
	List<T*>*
	get_nodes ()
	{
		List<T*>* result = new List<T*>;
		foreach (vertex_pt v, vertices(bs))
		{
			PT_node* node = vn[v];
			if (isa<T> (node))
				result->push_back (dyc<T> (node));
		}
		return result;
	}


private:
	PT_graph bs;

	friend class PT_edge;
	friend class PT_node;
};


// TODO: do we want the edge to have types?
class PT_edge : virtual public GC_obj
{
	Points_to* ptg;
public:
	edge_pt edge;

	PT_edge (Points_to* ptg, edge_pt edge)
	: ptg (ptg)
	, edge (edge)
	{
	}

	PT_node* get_source ()
	{
		return ptg->vn[source (edge, ptg->bs)];
	}

	PT_node* get_target ()
	{
		return ptg->vn[target (edge, ptg->bs)];
	}
};



class PT_node : virtual public GC_obj
{
public:
	Points_to* ptg;
	int index;
	vertex_pt vertex;

	// Each allocated node gets a unique index
	static int index_counter;

	PT_node (Points_to* ptg);
	virtual string graphviz_attrs () = 0;

	// I would prefer if this was not in the header, but what can you do.
	template<class T>
	List<T*>*
	get_pointees ()
	{
		List<T*>* result = new List<T*>;

		List<vertex_pt> worklist (this->vertex);
		Set<vertex_pt> seen;
		while (worklist.size ())
		{
			// Handle the worklist
			vertex_pt top = worklist.front();
			worklist.pop_front ();

			// Avoid cycles
			if (seen.has (top))
				continue;

			seen.insert (top);


			// Process nodes
			PT_node* node = ptg->vn[top];
			if (isa<T> (node))
				result->push_back (dyc<T> (node));
			else
			{
				// Add successors the worklist
				foreach (edge_pt out_edge, out_edges (vertex, ptg->bs))
					worklist.push_back (ptg->ee[out_edge]->get_target ()->vertex);
			}
		}

		return result;
	}

};

// TODO: different kinds of nodes for fields, variables, arrays, objects and
// atoms?
class Var_node : public PT_node
{
public:
	MIR::VARIABLE_NAME* var_name;

	Var_node (Points_to* ptg, MIR::VARIABLE_NAME* var_name);
	string graphviz_attrs ();
};

class Atom_node : public PT_node
{
public:
	MIR::Node* atom; // constant or literal

	Atom_node (Points_to* ptg, MIR::Node* atom);
	string graphviz_attrs ();
};


#endif // PHC_POINTS_TO
