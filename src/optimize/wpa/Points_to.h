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

/* TODO: split the edges into P and D (possible and definite from Emami94),
 * for may-alias and must-alias. */
#define DECL(T) class T; typedef List<T*> T##_node_list;

DECL (PT_node);
DECL (Zval_node);
DECL (Value_node);
DECL (Lit_node);
DECL (Unknown_node);
DECL (Storage_node);
DECL (Object_node);
DECL (Array_node);

DECL (PT_edge);
DECL (Named_edge);
DECL (Known_edge);
DECL (Unknown_edge);

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

// The reason for this class is so that we can have NULL representing
// an uninitialized location.
class Location : virtual public GC_obj
{
public:
	Storage_node* node;
	string name;

	Location (Storage_node* node, string name)
	: node (node)
	, name (name)
	{
	}
};

class Points_to : virtual public GC_obj
{
	// 1 symtable per function
	// TODO: deal with recursion
	Map<string, Zval_node*> symtables;

public:
	Points_to ();

	// Accessors
	boost::property_map<PT_graph, vertex_pt_node_t>::type vn;

	// ee = (BGL) edge -> (PTG) edge
	boost::property_map<PT_graph, edge_pt_edge_t>::type ee;


	void consistency_check ();
	void dump_graphviz (String* label);

public:

	// Setup the function's symtable
	void setup_function (string ns);

	// Remove the function's symtable, and clear unreachable nodes.
	void clear_function (string ns); 

	// Provide a name for the locations for fields, array_indices, etc.
	// This does not return a node in the graph, or affect anything in the
	// graph. It just packages it.
	Location* get_location (string ns, MIR::VARIABLE_NAME* var);
	Location* get_location (string ns, MIR::FIELD_NAME* field);
	Location* get_location (string ns, MIR::Literal* index);


	// Add an array, and return the node.
	Array_node* add_array_node (string ns);

	// Add a literal and return the node.
	Lit_node* add_lit_node (string ns, MIR::Literal* lit);

	// Add a literal and return the node.
	Zval_node* add_zval_node (string ns);

	// Gets the zval node for the location. If there is none, UNINIT_ZVAL is
	// returned, unless INIT is set, in which case a Zval_node is added to the
	// graph (pointed to by LOC's edge, and pointing to a new NIL Lit_node.
	Zval_node* get_zval_node (Location* loc, bool init);


	// Set LOC's value to VAL
	void set_value (Location* loc, Value_node* val);

	// Set LOC1's value to LOC2's value. If Loc2 is missing, just copy NULL,
	// without touching Loc2.
	void copy_value (Location* loc1, Location* loc2);

	// Make LOC1 point to the same zval as LOC2. If LOC2 is UNINIT, create a
	// new node for it.
	void set_reference (Location* loc1, Location* loc2);

private:
	// Low-level API
	PT_edge* add_edge (PT_node*, PT_node*);
	Named_edge* add_named_edge (Location* loc, Zval_node*);
	void remove_named_edge (Location* loc);

	// Add the node to the graph, and return it.
	template <class T>
	T* add_node (T* node)
	{
		assert (node->vertex == NULL);
		vertex_pt v = add_vertex (bs);
		vn[v] = node;
		node->vertex = v;

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
	friend class Storage_node;
};


// TODO: do we want the edge to have types?
class PT_edge : virtual public GC_obj
{
public:
	Points_to* ptg;
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

	virtual string graphviz_attrs ()
	{
		return "";
	}
};

class Named_edge : public PT_edge
{
public:
	string name;
	Named_edge (string name, Points_to* ptg, edge_pt edge)
	: PT_edge (ptg, edge)
	, name (name)
	{
	}

	string graphviz_attrs ()
	{
		stringstream ss;
		ss << "label=\"" << name << "\"";
		return ss.str ();
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

	PT_node (); // required for Value_node()
	PT_node (Points_to* ptg, string ns);
	virtual string graphviz_attrs () = 0;

	// I would prefer if this was not in the header, but what can you do.
	// TODO: i dont think this is really necessary anymore, given that we cant
	// traverse other nodes.
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

	template<class T>
	T*
	get_solo_pointee ()
	{
		List<T*>* pointees = get_pointees<T> ();
		assert (pointees->size () == 1);
		return pointees->front ();
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

// TODO: Only flow sensitivity to go.

/*
 * To represent multiple possible values, a ZVP node can point to multiple
 * Value_nodes.
 */

class Value_node : virtual public PT_node
{
public:
	Value_node ();
	virtual Value_node* clone () = 0;
};

class Lit_node : public Value_node
{
public:
	MIR::Literal* lit;

	Lit_node (Points_to* ptg, string ns, MIR::Literal* lit);
	string graphviz_attrs ();
	Value_node* clone ();
};

// This is simply storage for analysis results which depend on dataflow. For
// example, if $x can be 5 or a string, x would point to two zvals, one a
// Lit(5), the other an unknown (type=string).
class Unknown_node : virtual public Value_node
{
public:
	Unknown_node (Points_to* ptg, string ns, MIR::Literal* lit);
	string graphviz_attrs ();
	Value_node* clone ();
};

class Storage_node : virtual public Value_node
{
public:
	// Return NULL if the node doesnt exist
	// TODO: presumably this could return multiple nodes?
	Zval_node* get_indexed (string index);
	void remove_named_edge (string index);
};

/* A symtable is just an array. Each method will have a zval which points to
 * the object representing the symtable. */

class Array_node : public Storage_node
{
public:
	Array_node (Points_to* ptg, string ns);
	string graphviz_attrs ();
	Value_node* clone ();
};

// Not sure how this differs from an Objet node. I expect it just means it
// will have a type.
class Object_node : public Storage_node
{
public:
	Object_node (Points_to* ptg, string ns);
	string graphviz_attrs ();
	Value_node* clone ();
};

/* 
 * I can generalize Vars to indices in a global array. In fact, the
 * generalization is the same in all cases:
 *		- array index:
 *			a named edge from an ARRAY to a value.
 *		- object field:
 *			a named edge from an OBJECT to a value.
 *		- variable_name:
 *			a named edge from a SYMTABLE to a value.
 *
 *	Indexes can only be INTs or STRINGs (though they can be unknown for
 *	var-vars, variable indices, and var-fields).
 *
 * Although they can be strings or ints, really ca be represented by just one
 * type. For different operations, "5" may be a string or int index, but it
 * does not vary for that operation (var-vars: always strings, var-fields:
 * always strings, arrays:always ints). So we only need strings her (aka
 * Known_edge).
 */

// TODO: is a named edge a known edge? i think so.
class Known_edge : virtual public PT_edge
{
};

class Unknown_edge : virtual public PT_edge
{
};

// TODO: for handling possibly/definitely edges, we could always create a
// definitely node (pointing to NULL), which is killed or merged. But that
// doesnt model unset variables, which might be nice (not definitely useful
// though).


#endif // PHC_POINTS_TO
