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

#define DECL(T) class T; typedef List<T*> T##_list;

DECL (PT_node);
DECL (Index_node);
DECL (Storage_node);

Storage_node* SN (string scope);
Index_node* IN (string scope, string name);
Index_node* VN (string scope, MIR::VARIABLE_NAME*);
Index_node* FN (string scope, MIR::FIELD_NAME*);
//Index_node* AN (string scope, string array_index); TODO


// A node in the graph (ie the abstract base of the components of an alias-pair).
class PT_node : virtual public GC_obj
{
public:
	// Each PT node gets a unique name for the alias pairs representation.
	virtual string get_unique_name () = 0;
	virtual String* get_graphviz () = 0;
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
 *	attributes in here (they should be in the other analyses' lattices, indexed
 *	by get_unique_name ()).
 */
class Index_node : public PT_node
{
public:
	// The storage node containing this node.
	string storage;

	// The name of the node (* for unnamed)
	string name;

	// Get the unnamed index representing var-vars, var-fields and array
	// indexes.
	static Index_node* get_unnamed (string storage);

	Index_node (string storage, string name);
	string get_unique_name ();

	String* get_graphviz ();
};



// Represents class for arrays, objects and symtables
class Storage_node : public PT_node
{
public:
	Storage_node (string name);

	string name;

	// If true, its (outgoing) edges cannot be killed, as it represents more
	// than one run-time object. If false, represents just one run-time object,
	// meaning its edges can be killed. 
	bool is_abstract;

	string get_unique_name ();

	String* get_graphviz ();
};

class Alias_pair : virtual public GC_obj
{
public:
	Alias_pair (PT_node* source, PT_node* target, certainty cert);
	PT_node* source;
	PT_node* target;
	certainty cert;

	void dump();
};

/*
 * NOTE:
 *		All PT_nodes are simply descriptors for nodes. They do not provide a
 *		means to access the node itself.
 *
 *		Note too that the index_node is merely a unique point in the graph. There
 *		is no direct mapping to PHP constructs, as some are more compicated that
 *		that. For example: $x =& $x[$y], is an Index_node indexed by another
 *		index_node, and can refer to multiple index_node.
 *
 *		The result is that Points_to just does the graphing, and that Aliasing
 *		provides the abstraction layer over that, with which to interface with
 *		the MIR, and other analyses.
 */

class Points_to : virtual public GC_obj
{
private:
	Set<Alias_pair*> all_pairs; // makes it easier to clone
	Map<string, Map<string, Alias_pair*> > by_source;
	Map<string, Map<string, Alias_pair*> > by_target;

public:
	Points_to ();


	void open_scope (string name);
	void close_scope (string name);

	void add_node (Index_node* node);
	void add_edge (PT_node* n1, PT_node* n2, certainty = DEFINITE);
	void add_bidir_edge (PT_node* n1, PT_node* n2, certainty cert = DEFINITE);

	void kill_value (Index_node* index);
	void kill_references (Index_node* index);

	void set_scalar_value (Index_node* lhs);
	void set_reference (Index_node* n1, Index_node* n2);
	void copy_value (Index_node* n1, Index_node* n2);

	bool contains (Index_node* node);

	bool has_value_edges (Index_node* node);

	void dump_graphviz (String* label);

	void remove_unreachable_nodes ();

	Index_node_list* get_references (Index_node* index, certainty cert);
	Storage_node_list* get_points_to (Index_node* index, certainty cert);

	Index_node_list* get_local_references (Storage_node* ns, Index_node* index, certainty cert);

private:
	// Get the list of indices that alias INDEX, with the certainty CERT.
	// Must-aliases are not returned for POSSIBLE. NODE is not returned, so
	// callers which rely on NODE aliasing itself must handle it themselves.
	template <class T>
	List<T*>* get_aliases (Index_node* node, certainty cert)
	{
		return get_targets<T> (node, cert);
	}

	template <class T>
	List<T*>* get_targets (PT_node* node, certainty cert = PTG_ALL)
	{
		List<T*>* result = new List<T*>;

		string source = node->get_unique_name ();

		// There must be an edge to anything it aliases
		string target;
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

	template <class T>
	List<T*>* get_nodes ()
	{
		List<T*>* result = new List<T*>;

		// Keep track of already added ones
		Map<string, PT_node*> all;

		foreach (Alias_pair* pair, all_pairs)
		{
			if (isa<T> (pair->source))
				all[pair->source->get_unique_name ()] = pair->source;

			if (isa<T> (pair->target))
				all[pair->target->get_unique_name ()] = pair->target;
		}

		return result;
	}

	/*
	 * Low-level API
	 */

	void remove_node (PT_node* node);
	void insert (Alias_pair*);
	bool has_node (PT_node* node);

	void remove_pair (PT_node* n1, PT_node* n2, bool expected = true);


public:
	Points_to* clone();
};

#endif // PHC_POINTS_TO
