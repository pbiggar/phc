/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Points-to graph.
 *
 *
 */

#ifndef PHC_POINTS_TO
#define PHC_POINTS_TO

#include "lib/List.h"
#include "lib/String.h"
#include "lib/Set.h"
#include "lib/Map.h"

#include "MIR.h"

#include "WPA.h"

DECL (PT_node);
DECL (Index_node);
DECL (Storage_node);

SET_COMPARABLE (Points_to);

Storage_node* SN (string scope);
Index_node* IN (string scope, string name);
Index_node* VN (string scope, MIR::VARIABLE_NAME*);
Index_node* FN (string scope, MIR::FIELD_NAME*);
//Index_node* AN (string scope, string array_index); TODO arrays

Value_node* ABSVAL (Index_node* node);
Storage_node* CX_array_node (Context cx);
Storage_node* CX_object_node (Context cx);
Storage_node* CX_symtable_node (Context cx);



// A node in the graph (ie the abstract base of the components of an
// alias-pair).
class PT_node : virtual public GC_obj
{
public:
	// Each PT node gets a unique name for the alias pairs representation.
	virtual Alias_name name () = 0;
	virtual String* get_graphviz_label () = 0;

	virtual PT_node* convert_context_name () = 0;
};

/*
 * An index_node represents a variable, array-index or field of a storage node.
 *
 * It comprises a descriptor, the storage node's name, and the index name.
 * There is not a unique descriptor for this node. Any object with the same
 * descriptor represents the same node, in any graph. So we cannot store
 * attributes in here (they should be in the other analyses' lattices, indexed
 * by node->name ().str ()).
 */
class Index_node : public PT_node
{
public:
	// The name of the storage node which this indexes.
	const string storage;

	// The name of the node (can be UNKNOWN)
	const string index;

public:
	Index_node (string storage, string index);

	virtual Alias_name name ();
	virtual String* get_graphviz_label ();
	virtual Index_node* convert_context_name ();
	virtual Storage_node* get_owner ();
};



// Represents class for arrays, objects and symtables.
class Storage_node : public PT_node
{
public:
	const string storage;

public:
	Storage_node (string storage);

	virtual Alias_name name ();
	virtual String* get_graphviz_label ();
	virtual Storage_node* convert_context_name ();

public:
	// Return a string suitable to be put as the prefix of an index_name.
	virtual string for_index_node ();
};

// This represents the value of the node that points to it. It is used as the
// name for scalars and such. It is tricky to track that information if only
// storage nodes are used, as the possible/definite thing is difficult.
class Value_node : public Storage_node
{
public:
	Value_node (Index_node* owner);
	Value_node (string owner);

	Alias_name name ();
	String* get_graphviz_label ();
	Value_node* convert_context_name ();

public:
	string for_index_node ();
};


// Just a pair really, but I didnt want to have to remember which was FIRST and which was SECOND.
class Reference
{
public:
	Reference (Index_node* index, Certainty cert)
	: index(index)
	, cert(cert)
	{
	}

public:
	Index_node* const index;
	const Certainty cert;
};

typedef List<Reference*> Reference_list;

template <class Source_type, class Target_type>
class Alias_pair : virtual public GC_obj
{
protected:
	typedef Alias_pair<Source_type, Target_type> parent;

public:

	Alias_pair (Source_type* source, Target_type* target)
	: source (source)
	, target (target)
	{
	}

	bool equals (parent* other)
	{
		Alias_name this_source = this->source->name();
		Alias_name this_target = this->target->name();
		Alias_name other_source = other->source->name();
		Alias_name other_target = other->target->name();

		return true
			&& this_source == other_source
			&& this_target == other_target
			;
	}

	void dump()
	{
		CHECK_DEBUG ();
		cdebug
			<< source->name ().str() << " -> "
			<< target->name ().str()
			;
	}

	Source_type* const source;
	Target_type* const target;
};

// Cert is kept outside the edge. It is returned from Points-to via Reference.
typedef Alias_pair<Index_node, Index_node> Reference_edge;
typedef Alias_pair<Index_node, Storage_node> Points_to_edge; 
typedef Alias_pair<Storage_node, Index_node> Field_edge; 

DECL_LIST (Points_to_edge);
DECL_LIST (Field_edge);
DECL_LIST (Reference_edge);

SET_COMPARABLE (Points_to_edge);
SET_COMPARABLE (Field_edge);
SET_COMPARABLE (Reference_edge);


/*
 * NOTE:
 *
 *	All PT_nodes are simply descriptors for nodes. They do not provide a means
 *	to access the node itself.
 *
 *	Note too that the index_node is merely a unique point in the graph. There
 *	is no direct mapping to PHP constructs, as some are more compicated that
 *	that. For example: $x =& $x[$y], is an Index_node indexed by another
 *	Index_node, and can refer to multiple index_nodes.
 *
 *	The result is that Points_to just does the graphing. Paths and P provide the
 *	abstraction layer over the lower-level representation of PT_nodes, and there
 *	is a 1-to-1 correspondence between MIR nodes and paths.
 */

template <class Source_type, class Target_type, class Edge_type, class Value_type>
class Pair_map
{
	typedef Source_type source_type;
	typedef Target_type target_type;
	typedef Edge_type edge_type;
public:

	// Storing values
	Value_type get_value (Edge_type* edge)
	{
		return this->get_value (edge->source, edge->target);
	}

	Value_type get_value (Source_type* source, Target_type* target)
	{
		phc_TODO ();
	}

	void set_value (Edge_type* pair, Value_type value)
	{
		phc_TODO ();
	}

	// Returning members
	List<Target_type*>* get_targets (Source_type* source)
	{
		List<Target_type*>* result = new List<Target_type*>;

		foreach (Edge_type* edge, *by_source[source->name()].values ())
			result->push_back (edge->target);

		return result;
	}

	List<Source_type*>* get_sources (Target_type* target)
	{
		List<Source_type*>* result = new List<Source_type*>;

		foreach (Edge_type* edge, *by_target[target->name()].values ())
			result->push_back (edge->source);

		return result;
	}

	// Equality
	bool equals (Pair_map<Source_type, Target_type, Edge_type, Value_type>* other)
	{
		phc_TODO ();
	}

	void add_edge (Source_type* source, Target_type* target)
	{
		if (this->has_edge (source, target))
			return;

		by_source [source->name ()][target->name ()] = new Edge_type (source, target);
		by_target [target->name ()][source->name ()] = new Edge_type (source, target);
	}

	bool has_edge (Source_type* source, Target_type* target)
	{
		bool result = (by_source[source->name()].has (target->name()));

		assert (result == (by_target[target->name()].has (source->name())));

		return result;
	}

	void remove_edge (Source_type* source, Target_type* target)
	{
		by_source[source->name()].erase (target->name ());
		by_target[target->name()].erase (source->name ());
		values[source->name()].erase (target->name());
	}

	List<Edge_type*>* get_edges ()
	{
		List<Edge_type*>* result = new List<Edge_type*>;

		typedef Map<Alias_name, Edge_type*> Map_type;
		foreach (Map_type& map, *by_source.values ())
			result->push_back_all (map.values ());

		return result;
	}

	void remove_all_incoming_edges (Target_type* target)
	{
		foreach (Source_type* source, *this->get_sources (target))
			this->remove_edge (source, target);
	}

	void remove_all_outgoing_edges (Source_type* source)
	{
		foreach (Target_type* target, *this->get_targets (source))
			this->remove_edge (source, target);
	}




private:
	Map<Alias_name, Map<Alias_name, Value_type> > values;
	Map<Alias_name, Map<Alias_name, Edge_type*> > by_source;
	Map<Alias_name, Map<Alias_name, Edge_type*> > by_target;
};

struct Empty{};

template <class Source_type, class Target_type, class Edge_type>
class Pair_set : public Pair_map<Source_type, Target_type, Edge_type, Empty>, virtual public GC_obj
{
private:
	Empty get_value (Edge_type* edge) { phc_unreachable (); }
	void set_value (Edge_type* edge, Empty value) { phc_unreachable (); }
};

class Points_to : virtual public GC_obj
{
private:
	// This keeps count of whether something is abstract or not (subsuming
	// whether it is in scope).
	// TODO: the is_symtable function is wrong
	Map<Alias_name, int> abstract_counts;

	// The set of storage nodes which are a function's symbol table.
	Set<Alias_name> symtables;


	// (Index_node, Index_node) -> certainty.
	// SOURCE and TARGET alias each other, with some CERTAINTY in { POSSIBLE,
	// DEFINITE }.
	Pair_map<Index_node, Index_node, Reference_edge, Certainty> references;

	// (Index_node, Storage_node) set.
	// SOURCE is an index points-to TARGET. Its certainty is determined
	// implicitly by the number of points-to edges from SOURCE.
	Pair_set<Index_node, Storage_node, Points_to_edge> points_to;

	// TARGETs are indices of SOURCE. A certainty doesn't make sense.
	// (Storage_node, Index_node) set.
	Pair_set<Storage_node, Index_node, Field_edge> fields;

public:
	Points_to ();

	void open_scope (Storage_node* st);
	void close_scope (Storage_node* st);
	bool is_abstract (Storage_node* st);
	bool is_abstract_field (Index_node* index);
	bool is_symtable (Storage_node* st);

	/*
	 * Reference
	 */

	// References are (target, certainty) pairs. Don't confuse them with
	// Reference_edges.
	Reference_list* get_references (Index_node* source, Certainty cert = PTG_ALL);
	void set_reference_cert (Reference_edge* edge, Certainty cert);

	void add_reference (Index_node* source, Index_node* target, Certainty cert);
	bool has_reference (Index_node* source, Index_node* target);

	// Just removes the reference
	void remove_reference (Index_node* source, Index_node* target);

	/*
	 * Points-to edges
	 */

	// Storage nodes that index_node points-to.
	Storage_node_list* get_points_to (Index_node* index);
	Index_node_list* get_points_to_incoming (Storage_node* st);

	void add_points_to (Index_node* source, Storage_node* target);
	bool has_points_to (Index_node* source, Storage_node* target);

	// Removes the points-to edge, and nothing else. The caller must ensure that
	// the index is not left pointing to nothing.
	void remove_points_to (Index_node* source, Storage_node* target);


	/*
	 * Field edges
	 */

	Index_node_list* get_fields (Storage_node* storage);

	// The storage node of an index node is implicit (in the STORAGE field).
	void add_field (Index_node* target);
	bool has_field (Index_node* target);

	// Remove the edge from the storage-node to the index-node. Also removes
	// outgoing points-to edges, and reference edges.
	void remove_field (Index_node* target);


	/*
	 * Nodes
	 */

	PT_node_list* get_nodes ();

	bool has_storage_node (Storage_node* st);

	void remove_index_node (Index_node* index);
	void remove_storage_node (Storage_node* st);

	Storage_node_list* get_storage_nodes ();

	/*
	 * Whole graph.
	 */

	bool equals (Points_to* other);
	void dump_graphviz (String* label, Context cx, Whole_program* wp);

	Points_to* clone();
	Points_to* merge (Points_to* other);

	void consistency_check (Context cx, Whole_program* wp);



	/*
	 * TODO: From here on, everything should be vetted (and hopefully killed)
	 */

	static Index_node_list* get_possible_nulls (List<Points_to*>* graphs);



	// A lot of points in the graph use names derived from some context. Change
	// them to use a non-contextual version.
	void convert_context_names ();

	/*
	 * Lower-level API
	 */

private:

	void remove_unreachable_nodes ();

	void remove_node (PT_node* node);


/*	template <class T>
	List<T*>* get_incoming (PT_node* node, Certainty cert = PTG_ALL)
	{
		List<T*>* result = new List<T*>;

		Alias_name target = node->name ();

		// There must be an edge to anything it aliases
		Alias_name source;
		Alias_pair* pair;
		foreach (boost::tie (source, pair), by_target[target])
		{
			if ((pair->cert & cert) // bitwise: PTG_ALL matches both
				&& isa<T> (pair->source))
			{
				result->push_back (dyc<T>(pair->source));
			}
		}

		return result;
	}

	template <class T>
	List<T*>* get_targets (PT_node* node, Certainty cert = PTG_ALL)
	{
		List<T*>* result = new List<T*>;

		Alias_name source = node->name ();

		// There must be an edge to anything it aliases
		Alias_name target;
		Alias_pair* pair;
		foreach (boost::tie (target, pair), by_source[source])
		{
			if ((pair->cert & cert) // bitwise: PTG_ALL matches both
				&& isa<T> (pair->target))
			{
				result->push_back (dyc<T>(pair->target));
			}
		}

		return result;
	}
*/

};

#endif // PHC_POINTS_TO
