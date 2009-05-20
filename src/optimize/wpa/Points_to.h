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
 * These represent Variables, array-indices and fields of storage nodes.
 *
 * This descriptor is a combination of their storage node and their index.
 *		Global var-vars: GST::*
 *		Local (to function a()) variable 'x': a.ST::x
 *
 *	There is not a unique descriptor for this node. Any object with the same
 *	descriptor represents the same node, in any graph. So we cannot store
 *	attributes in here (they should be in the other analyses' lattices,
 *	indexed by name ().str ()).
 */
class Index_node : public PT_node
{
public:
	// The storage node containing this node.
	string storage;

	// The name of the node (* for unnamed)
	string index;

	// Get the unnamed index representing var-vars, var-fields and array
	// indexes.
	static Index_node* get_unnamed (string storage);

	Index_node (string storage, string index);
	Alias_name name ();

	String* get_graphviz_label ();

	Index_node* convert_context_name ();
};



// Represents class for arrays, objects and symtables.
class Storage_node : public PT_node
{
public:
	// If we can touch this, we can ruin Value_node.
	string storage;

	Storage_node (string storage);

	// Return a string suitable to be put as the prefix of an index_name.
	virtual string for_index_node ();


	virtual Alias_name name ();

	virtual String* get_graphviz_label ();


	virtual Storage_node* convert_context_name ();
};

// This represents the value of the node that points to it. It is used as the
// name for scalars and such. It is tricky to track that information if only
// storage nodes are used, as the possible/definite thing is difficult.
class Value_node : public Storage_node
{
public:
	Value_node (Index_node* owner);
	Value_node (string owner);

	string for_index_node ();

	Alias_name name ();

	String* get_graphviz_label ();

	Value_node* convert_context_name ();
};

class Alias_pair : virtual public GC_obj
{
public:
	Alias_pair (PT_node* source, PT_node* target);
	PT_node* source;
	PT_node* target;

	bool equals (Alias_pair* other);
	void dump();
};


SET_COMPARABLE (Alias_pair);


/*
 * NOTE:
 *		All PT_nodes are simply descriptors for nodes. They do not provide a
 *		means to access the node itself.
 *
 *		Note too that the index_node is merely a unique point in the graph.
 *		There is no direct mapping to PHP constructs, as some are more
 *		compicated that that. For example: $x =& $x[$y], is an Index_node
 *		indexed by another Index_node, and can refer to multiple index_nodes.
 *
 *		The result is that Points_to just does the graphing. Paths and P
 *		provide the abstraction layer over the lower-level representation of
 *		PT_nodes, and there is a 1-to-1 correspondence between MIR nodes and
 *		paths.
 */

DECL (Alias_pair);

template <class S, class T, class V>
class Pair_map
{
public:

	// Storing values
	V get_value (Alias_pair* pair)
	{
		phc_TODO ();
	}

	void set_value (Alias_pair* pair, V value)
	{
		phc_TODO ();
	}

	// Returning members
	List<T*>* get_targets (S* source)
	{
		phc_TODO ();
	}

	Alias_pair_list* get_pairs ()
	{
		phc_TODO ();
	}

	// Equality
	bool equals (Pair_map<S, T, V>* other)
	{
		phc_TODO ();
	}


private:
	Map<Alias_name, Map<Alias_name, V> > values;
	Map<Alias_name, Map<Alias_name, Alias_pair*> > by_source;
	Map<Alias_name, Map<Alias_name, Alias_pair*> > by_target;
};

struct Empty{};

template <class S, class T>
class Pair_set : public Pair_map<S, T, Empty>, virtual public GC_obj
{
private:
	Empty get_value (Alias_pair* pair) { phc_unreachable (); }
	void set_value (Alias_pair* pair, Empty value) { phc_unreachable (); }
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
	Pair_map<Index_node, Index_node, Certainty> references;

	// (Index_node, Storage_node) set.
	// SOURCE is an index points-to TARGET. Its certainty is determined
	// implicitly by the number of points-to edges from SOURCE.
	Pair_set<Index_node, Storage_node> points_to;

	// TARGETs are indices of SOURCE. A certainty doesn't make sense.
	// (Storage_node, Index_node) set.
	Pair_set<Storage_node, Index_node> fields;

public:
	Points_to ();

	bool equals (Points_to* other);
	void dump_graphviz (String* label, Context cx, Whole_program* wp);

	void open_scope (Storage_node* st);
	void close_scope (Storage_node* st);
	bool is_abstract (Storage_node* st);
	bool is_symtable (Storage_node* st);

	// Get the full list of storage nodes.


	void insert (Alias_pair*, Certainty cert);

	// Set the CERTAINTY for PAIR.
	void set_reference_cert (Alias_pair* pair, Certainty cert);

	// Get the nodes indexing INDEX, with certainty CERT.
	Index_node_list* get_references (Index_node* index, Certainty cert);

	// Return the indices pointed-to by by STORAGE
	Index_node_list* get_fields (Storage_node* storage);

	// Return the storage_nodes pointed to by INDEX.
	Storage_node_list* get_dereferenced (Index_node* index);

	// Return the storage node pointing to INDEX.
	Storage_node* get_owner (Index_node* index);

	void consistency_check (Context cx, Whole_program* wp);

	Storage_node_list* get_storage_nodes ();

	static Index_node_list* get_possible_nulls (List<Points_to*>* graphs);


	Storage_node* get_named_node (string name);

	PT_node_list* get_nodes ();


	/*
	 * Lower-level API
	 */

	void add_index (Index_node* node, Certainty);
	void add_edge (PT_node* n1, PT_node* n2, Certainty);
	void add_bidir_edge (PT_node* n1, PT_node* n2, Certainty cert);

	bool has_node (PT_node* node);

	// Returns NULL if the edge is missing. We use this in place of a
	// has_edge() function, since we need to find out its CERTAINTY.
	Alias_pair* get_edge (PT_node* source, PT_node* target);

	void remove_unreachable_nodes ();
	void maybe_remove_node (PT_node*);

	void remove_node (PT_node* node);
	void remove_pair (PT_node* source, PT_node* target, bool expected = true);
	void remove_pair (Alias_pair* pair, bool expected = true);

	Points_to* clone();
	Points_to* merge (Points_to* other);

	// A lot of points in the graph use names derived from some context. Change
	// them to use a non-contextual version.
	void convert_context_names ();

private:

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
