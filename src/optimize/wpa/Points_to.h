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
class Loc_node;
class Zval_node;
class Value_node;

/* TODO: split the edges into P and D (possible and definite from Emami94), for
 * may-alias and must-alias. */
class PT_edge;


typedef List<PT_node*> PT_node_list;
typedef List<PT_edge*> PT_edge_list;

typedef List<PT_node*> PT_node_list;
typedef List<Zval_node*> Zval_node_list;
typedef List<Value_node*> Value_node_list;
typedef List<Loc_node*> Loc_node_list;


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
	Map<string, Var_map<Loc_node*> > var_maps;

public:
	Points_to ();

	// Accessors
	boost::property_map<PT_graph, vertex_pt_node_t>::type vn;

	// ee = (BGL) edge -> (PTG) edge
	boost::property_map<PT_graph, edge_pt_edge_t>::type ee;



	void consistency_check ();
	void dump_graphviz (String* label);

public:
	// High-level API
	void set_reference (string source_ns, MIR::VARIABLE_NAME* source, string target_ns, MIR::VARIABLE_NAME* target);
	void set_value (string source_ns, MIR::VARIABLE_NAME* source, string target_ns, MIR::VARIABLE_NAME* target);
	void set_value (string source_ns, MIR::VARIABLE_NAME* source, MIR::Literal* target);


	// Return the location node for LOC, or NULL if none currently exists.
	Loc_node* get_loc_node (string ns, MIR::VARIABLE_NAME* loc);

private:
	// Low-level API
	PT_edge* add_edge (PT_node*, PT_node*);

	// Add the node to the graph, and return it.
	template <class T>
	T* add_node (T* node)
	{
		assert (node->vertex == NULL);
		vertex_pt v = add_vertex (bs);
		vn[v] = node;
		node->vertex = v;

		node->add_node_hook ();

		return node;
	}

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
			if (T* n = dynamic_cast<T*> (vn[v]))
				result->push_back (n);
		}
		return result;
	}


private:
	PT_graph bs;

	friend class PT_edge;
	friend class PT_node;
	friend class Loc_node;
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

	// The namespace of the node. This should be the name of the method in which
	// it appears (or Class_name::method_name, if applicable).
	// TODO: I'm not sure whether only the location node needs a namespace, but
	// it may be useful for arrays etc too (or we might use callstrings for
	// them).
	string ns;

	// Each allocated node gets a unique index
	static int index_counter;

	PT_node (Points_to* ptg, string ns);
	virtual string graphviz_attrs () = 0;

	// This is a workaround to a dependency problem. I'd like to do something
	// specific Loc_nodes in Points_to, but it requires looking inside the
	// Loc_node, which I cant do until I define Loc_node. Which I cant do until
	// I define PT_node. Which I cant do until I define Points_to. So something
	// has to give. This is probably the least ugly way.
	virtual void add_node_hook () {};

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
				foreach (edge_pt out_edge, out_edges (top, ptg->bs))
					worklist.push_back (ptg->ee[out_edge]->get_target ()->vertex);
			}
		}

		return result;
	}

	void remove_outgoing_edges ()
	{
		// The iterator is invalidated every time.
		while (out_degree (vertex, ptg->bs))
		{
			// nicer syntax than doing it manually
			foreach (edge_pt out_edge, out_edges (vertex, ptg->bs))
			{
				boost::remove_edge (out_edge, ptg->bs);
				break; // intensional. The foreach only has 1 iteration.
			}
		}
	}

};

// TODO: different kinds of nodes for fields, variables, arrays, objects and
// atoms?

/*
 * A location is a symbol-table location, which roughly corresponds to a
 * variable. This is split from the Zval_node since multiple variables can
 * point to the same zval.
 */
class Loc_node : public PT_node
{
public:
	MIR::VARIABLE_NAME* var_name;

	Loc_node (Points_to* ptg, string ns, MIR::VARIABLE_NAME* var_name);
	string graphviz_attrs ();

	void add_node_hook ();
};

/*
 * A zval is pointed to by one or more locations. If more than 1, it is in a
 * change-on-write set (ie they all alias zval. It points to one or more Value
 * nodes. If more than 1, it can have any of the values.
 */
class Zval_node : public PT_node
{
public:
	Zval_node (Points_to* ptg, string ns);
	string graphviz_attrs ();
};

/* To represent multiple possible values, a ZVP node can point to multiple
 * Value_nodes. */
// TODO: values can also be Objects and Arrays
// TODO: add special value nodes which do not represent a specific value, but
// can be used for summary values, for VRP, type-inference etc. These represent
// values for which we do not have a specific value, but might have a range of
// values, types, etc.



class Value_node : public PT_node
{
public:
	MIR::Literal* lit;

	Value_node (Points_to* ptg, string ns, MIR::Literal* lit);
	string graphviz_attrs ();
	Value_node* clone ();
};


#endif // PHC_POINTS_TO
