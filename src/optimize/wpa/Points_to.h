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

#include "MIR.h"

#include "lib/List.h"
#include "lib/String.h"
#include "lib/Set.h"
#include "lib/Map.h"


#include "WPA.h"

DECL (Index_node);
DECL (Storage_node);
DECL (Path);

SET_COMPARABLE (Points_to);

Storage_node* SN (string scope);
Index_node* IN (string scope, string name);
Index_node* VN (string scope, MIR::VARIABLE_NAME*);
Index_node* FN (string scope, MIR::FIELD_NAME*);

Value_node* SCLVAL (const Index_node* node);
Storage_node* CX_array_node (Context* cx);
Storage_node* CX_object_node (Context* cx);
Storage_node* CX_symtable_node (Context* cx);


/*
 * An index_node represents a variable, array-index or field of a storage node.
 *
 * It comprises a descriptor, the storage node's name, and the index name.
 * There is not a unique descriptor for this node. Any object with the same
 * descriptor represents the same node, in any graph. So we cannot store
 * attributes in here (they should be in the other analyses' lattices, indexed
 * by node.str ()).
 */
class Index_node : public Alias_name
{
public:
	// The name of the storage node which this indexes.
	const string storage;

	// The name of the node (can be UNKNOWN)
	const string index;

public:
	Index_node (string storage, string index);

	string str () const;
	String* get_graphviz_label () const;
	Index_node* convert_context_name () const;
	Index_node* get_starred_name () const;
	bool is_starred() const;
	Path* to_path () const;
};



// Represents class for arrays, objects and symtables.
class Storage_node : public Alias_name
{
public:
	const string storage;

public:
	Storage_node (string storage);

	virtual String* get_graphviz_label () const;
	virtual Storage_node* convert_context_name () const;
	string str () const;
};

// This represents the value of the node that points to it. It is used as the
// name for scalars and such. It is tricky to track that information if only
// storage nodes are used, as the possible/definite thing is difficult.
class Value_node : public Storage_node
{
public:
	Value_node (const Index_node* owner);
	Value_node (string owner);

	String* get_graphviz_label () const;
	Value_node* convert_context_name () const;
	string str () const;
};


namespace std
{
	template <>                                     
	struct equal_to <const Index_node*>
	{                                                     
		bool operator () (const Index_node* const an1, const Index_node* const an2) const
		{
			return *an1 == *an2;
		}
	};

	template <>                                     
	struct equal_to <Index_node*>
	{                                                     
		bool operator () (const Index_node*& an1, const Index_node*& an2) const
		{
			return *an1 == *an2;
		}
	};

	template <>                                     
	struct equal_to <const Storage_node*>
	{                                                     
		bool operator () (const Storage_node* const an1, const Storage_node* const an2) const
		{
			return *an1 == *an2;
		}
	};

	template <>                                     
	struct equal_to <Storage_node*>
	{                                                     
		bool operator () (const Storage_node*& an1, const Storage_node*& an2) const
		{
			return *an1 == *an2;
		}
	};

	template <>                                     
	struct equal_to <const Value_node*>
	{                                                     
		bool operator () (const Value_node* const an1, const Value_node* const an2) const
		{
			return *an1 == *an2;
		}
	};

	template <>                                     
	struct equal_to <Value_node*>
	{                                                     
		bool operator () (const Value_node*& an1, const Value_node*& an2) const
		{
			return *an1 == *an2;
		}
	};



	namespace tr1
	{
		template <>
		struct hash<Index_node>
		{
			size_t operator() (const Index_node& an) const
			{
				return an.hash ();
			}
		};

		template <>
		struct hash<const Index_node>
		{
			size_t operator() (const Index_node& an) const
			{
				return an.hash ();
			}
		};

		template <>
		struct hash<Index_node*>
		{
			size_t operator() (const Index_node*& an) const
			{
				return an->hash ();
			}
		};

		template <>
		struct hash<const Index_node*>
		{
			size_t operator() (const Index_node* const an) const
			{
				return an->hash ();
			}
		};


		template <>
		struct hash<Storage_node>
		{
			size_t operator() (const Storage_node& an) const
			{
				return an.hash ();
			}
		};

		template <>
		struct hash<const Storage_node>
		{
			size_t operator() (const Storage_node& an) const
			{
				return an.hash ();
			}
		};

		template <>
		struct hash<Storage_node*>
		{
			size_t operator() (const Storage_node*& an) const
			{
				return an->hash ();
			}
		};

		template <>
		struct hash<const Storage_node*>
		{
			size_t operator() (const Storage_node* const an) const
			{
				return an->hash ();
			}
		};


		template <>
		struct hash<Value_node>
		{
			size_t operator() (const Value_node& an) const
			{
				return an.hash ();
			}
		};

		template <>
		struct hash<const Value_node>
		{
			size_t operator() (const Value_node& an) const
			{
				return an.hash ();
			}
		};

		template <>
		struct hash<Value_node*>
		{
			size_t operator() (const Value_node*& an) const
			{
				return an->hash ();
			}
		};

		template <>
		struct hash<const Value_node*>
		{
			size_t operator() (const Value_node* const an) const
			{
				return an->hash ();
			}
		};
	}
}




// Just a pair really, but I didnt want to have to remember which was FIRST and which was SECOND.
DECL(Reference);
class Reference : virtual public GC_obj
{
public:
	Reference (const Index_node* index, Certainty cert)
	: index(index)
	, cert(cert)
	{
	}

public:
	const Index_node* const index;
	const Certainty cert;
};


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

	bool equals (parent* other) const
	{
		return *this->source == *other->source
			&&	 *this->target == *other->target;
	}

	void dump()
	{
		CHECK_DEBUG ();
		cdebug << source.str() << " -> " << target.str();
	}

	Source_type* const source;
	Target_type* const target;
};

// Cert is kept outside the edge. It is returned from Points-to via Reference.
typedef Alias_pair<const Index_node, const Index_node> Reference_edge;
typedef Alias_pair<const Index_node, const Storage_node> Points_to_edge; 
typedef Alias_pair<const Storage_node, const Index_node> Field_edge; 


DECL_CONST_LIST (Points_to_edge);
DECL_CONST_LIST (Field_edge);
DECL_CONST_LIST (Reference_edge);

SET_COMPARABLE (Points_to_edge);
SET_COMPARABLE (Field_edge);
SET_COMPARABLE (Reference_edge);


/*
 * NOTE:
 *
 *	All Alias_names are simply descriptors for nodes. They do not provide a means
 *	to access the node itself.
 *
 *	Note too that the index_node is merely a unique point in the graph. There
 *	is no direct mapping to PHP constructs, as some are more compicated that
 *	that. For example: $x =& $x[$y], is an Index_node indexed by another
 *	Index_node, and can refer to multiple index_nodes.
 *
 *	The result is that Points_to just does the graphing. Paths and P provide the
 *	abstraction layer over the lower-level representation of Alias_names, and there
 *	is a 1-to-1 correspondence between MIR nodes and paths.
 */

class Empty : virtual public GC_obj
{
public:
	bool operator!= (const Empty&) const { return false; }
	bool operator== (const Empty&) const { return true; }
};

class Empty_combiner
{
public:
	Empty operator()(const Empty, const Empty) { return Empty (); }
};


class Empty_default
{
public:
	static Empty default_value () { return Empty (); }
};

class Certainty_combiner
{
public:
	Certainty operator()(const Certainty c1, const Certainty c2)
	{
		return combine_certs (c1, c2);
	}
};

class Certainty_default
{
public:
	static Certainty default_value () { phc_unreachable (); }
};



template <class Source_type, class Target_type, class Edge_type, class Value_type = Empty, class Default = Empty_default, class Combiner = Empty_combiner>
class Pair_map : virtual public GC_obj
{
	typedef Source_type source_type;
	typedef Target_type target_type;
	typedef Edge_type edge_type;
	typedef Pair_map<Source_type, Target_type, Edge_type, Value_type, Default, Combiner> this_type;

public:

	// This can result in the edge being shared, which is fine.
	Pair_map<Source_type, Target_type, Edge_type, Value_type, Default, Combiner> (const this_type& other)
	: values (other.values)
	, by_source (other.by_source)
	, by_target (other.by_target)
	{
	}

	Pair_map<Source_type, Target_type, Edge_type, Value_type, Default, Combiner> ()
	{
	}


	// Storing values
	Value_type get_value (Edge_type* edge) const
	{
		return this->get_value (edge->source, edge->target);
	}

	Value_type get_value (Source_type* source, Target_type* target) const
	{
		assert (this->has_edge (source, target));

		return values[source][target];
	}

	void set_value (Edge_type* pair, Value_type value = Default::default_value ())
	{
		this->set_value (pair->source, pair->target, value);
	}

	void set_value (Source_type* source, Target_type* target, Value_type value = Default::default_value ())
	{
		values[source][target] = value;
	}

	List<Target_type*>* get_targets (Source_type* source) const
	{
		List<Target_type*>* result = new List<Target_type*>;

		foreach (Edge_type* edge, *by_source[source].values ())
			result->push_back (edge->target);

		return result;
	}

	List<Source_type*>* get_sources (Target_type* target) const
	{
		List<Source_type*>* result = new List<Source_type*>;

		foreach (Edge_type* edge, *by_target[target].values ())
			result->push_back (edge->source);

		return result;
	}

	List<Target_type*>* get_all_targets () const
	{
		List<Target_type*>* result = new List<Target_type*>;

		foreach (Edge_type* edge, *this->get_edges ())
			result->push_back (edge->target);

		return result;
	}

	List<Source_type*>* get_all_sources () const
	{
		List<Source_type*>* result = new List<Source_type*>;

		foreach (Edge_type* edge, *this->get_edges ())
			result->push_back (edge->source);

		return result;
	}

	List<Edge_type*>* get_edges () const
	{
		List<Edge_type*>* result = new List<Edge_type*>;

		typedef Map<Target_type*, Edge_type*> Map_type;
		foreach (Map_type& map, *by_source.values ())
			result->push_back_all (map.values ());

		return result;
	}



	// Equality
	bool equals (this_type* other) const
	{
		// Check the edges
		if (this->get_edges ()->size () != other->get_edges ()->size ())
			return false;

		foreach (Edge_type* e, *other->get_edges ())
			if (not this->has_edge (e))
				return false;

		// Check the values
		foreach (Edge_type* e, *other->get_edges ())
			if (this->get_value (e) != other->get_value (e))
				return false;

		return true;
	}


	void add_edge (Source_type* source, Target_type* target, Value_type v = Default::default_value ())
	{
		this->add_edge (new Edge_type (source, target), v);
	}

	void add_edge (Edge_type* edge, Value_type v = Default::default_value ())
	{
		if (this->has_edge (edge))
		{
			if (values[edge->source][edge->target] != v)
        phc_optimization_exception ("Adding a new value from a new target unsupported during alias analysis");
		}
		else
		{
			by_source [edge->source][edge->target] = edge;
			by_target [edge->target][edge->source] = edge;
		}

		values[edge->source][edge->target] = v;
	}

	bool has_edge (Edge_type* edge) const
	{
		return this->has_edge (edge->source, edge->target);
	}

	bool has_edge (Source_type* source, Target_type* target) const
	{
		bool result = (by_source[source].has (target));

		assert (result == (by_target[target].has (source)));

		return result;
	}

	bool has_target (Target_type* target) const
	{
		return by_target.has (target);
	}

	bool has_source (Source_type* source) const
	{
		return by_source.has (source);
	}

	void remove_edge (Source_type* source, Target_type* target)
	{
		by_source[source].erase (target);
		by_target[target].erase (source);
		values[source].erase (target);
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

	this_type* merge (this_type* other) const
	{
		this_type* result = new this_type (*this);

		foreach (Edge_type* e, *other->get_edges ())
		{
			if (result->has_edge (e))
			{
				Value_type combined = Combiner() (other->get_value (e), result->get_value (e));
				result->set_value (e, combined);
			}
			else
			{
				result->add_edge (e, other->get_value (e));
			}

		}

		return result;
	}

	// Returns a clone in which all the names are converted to context names.
	this_type* convert_context_names () const
	{
		this_type* result = new this_type;

		foreach (Edge_type* e, *this->get_edges ())
		{
			Edge_type* new_edge = new Edge_type (
				e->source->convert_context_name (),
				e->target->convert_context_name ());

			Value_type pre_merge_value = this->get_value (e);

			if (result->has_edge (new_edge))
			{
				Value_type combined = Combiner() (pre_merge_value, result->get_value (new_edge));
				result->set_value (new_edge, combined);
			}
			else
			{
				result->add_edge (new_edge, pre_merge_value);
			}
		}
		return result;
	}



private:
	Map<Source_type*, Map<Target_type*, Value_type> > values;
	Map<Source_type*, Map<Target_type*, Edge_type*> > by_source;
	Map<Target_type*, Map<Source_type*, Edge_type*> > by_target;
};

/*
 * Abstract is a state machine with 3 states:
 *		MISSING -> PRESENT -> ABSTRACT
 *
 *	ABSTRACT means its saturated, and so we can never get back from there.
 *	An ABSTRACT node can be removed however, if nothing points to it.
 */
namespace Abstract_state
{
	enum _as { MISSING = 0 /*default*/, PRESENT = 1, ABSTRACT = 2};
	typedef enum _as AS;

	AS inc (AS as);
	AS dec (AS as);
	AS merge (AS as1, AS as2);
}


class Points_to_impl : virtual public GC_obj
{
private:
	int reference_count;
	friend class Points_to;

private:
	// This keeps count of whether something is abstract or not (subsuming
	// whether it is in scope).
	Map<const Storage_node*, Abstract_state::AS> abstract_states;

	// The set of storage nodes which are a function's symbol table.
	Set<const Storage_node*> symtables;

	typedef Pair_map<const Index_node, const Index_node, const Reference_edge, Certainty, Certainty_default, Certainty_combiner> reference_pair_type;

	// (Index_node, Index_node) -> certainty.
	// SOURCE and TARGET alias each other, with some CERTAINTY in { POSSIBLE,
	// DEFINITE }.
	reference_pair_type references;

	// (Index_node, Storage_node) set.
	// SOURCE is an index points-to TARGET. Its certainty is determined
	// implicitly by the number of points-to edges from SOURCE.
	Pair_map<const Index_node, const Storage_node, const Points_to_edge> points_to;

	// TARGETs are indices of SOURCE. A certainty would indicate whether it is
	// initialized, but is probably a bit hard to do (and not worth it compared
	// to an 'is_initialized' analysis.
	// TODO: might be much easier with the new design.
	// (Storage_node, Index_node) set.
	Pair_map<const Storage_node, const Index_node, const Field_edge> fields;

public:
	Points_to_impl ();

	void open_scope (const Storage_node* st);
	void close_scope (const Storage_node* st);
	void inc_abstract (const Storage_node* st);
	void dec_abstract (const Storage_node* st);
	bool is_abstract (const Storage_node* st) const;
	bool is_abstract_field (const Index_node* index) const;
	bool is_symtable (const Storage_node* st) const;

	/*
	 * Reference
	 */

	// References are (target, certainty) pairs. Don't confuse them with
	// Reference_edges.
	cReference_list* get_references (const Index_node* source, Certainty cert = PTG_ALL) const;
	Certainty get_reference_cert (const Reference_edge* edge) const;
	Certainty get_reference_cert (const Index_node* source, const Index_node* target) const;

	void add_reference (const Index_node* source, const Index_node* target, Certainty cert);

	bool has_reference (const Reference_edge* edge) const;
	bool has_reference (const Index_node* source, const Index_node* target) const;

	// Just removes the reference
	void remove_reference (const Index_node* source, const Index_node* target);

	/*
	 * Points-to edges
	 */

	// Storage nodes that index_node points-to.
	cStorage_node_list* get_points_to (const Index_node* index) const;
	cIndex_node_list* get_points_to_incoming (const Storage_node* st) const;

	void add_points_to (const Index_node* source, const Storage_node* target);
	bool has_points_to (const Index_node* source, const Storage_node* target) const;

	// Removes the points-to edge, and nothing else. The caller must ensure that
	// the index is not left pointing to nothing.
	void remove_points_to (const Index_node* source, const Storage_node* target);


	/*
	 * Field edges
	 */

	cIndex_node_list* get_fields (const Storage_node* storage) const;

	// The storage node of an index node is implicit (in the STORAGE field).
	void add_field (const Index_node* field);
	bool has_field (const Index_node* field) const;

	const Storage_node* get_storage (const Index_node* field) const;
	cIndex_node_list* get_incoming (const Storage_node* st) const;

	// Remove the edge from the storage-node to the index-node. Also removes
	// outgoing points-to edges, and reference edges.
	void remove_field (const Index_node* target);

	// Try really really hard to find the "correct" owner of the index_node,
	// even if it is not in the graph, or the index_node is impossible
	// (SCLVAL->index for example).
	const Storage_node* get_owner (const Index_node* index) const;


	/*
	 * Nodes
	 */

	cAlias_name_list* get_nodes () const;
	cIndex_node_list* get_index_nodes () const;
	cStorage_node_list* get_storage_nodes () const;
	cField_edge_list* get_field_edges () const;
	cPoints_to_edge_list* get_points_to_edges () const;	
	cReference_edge_list* get_possible_reference_edges () const;
	cReference_edge_list* get_definite_reference_edges () const;

	bool has_storage_node (const Storage_node* st) const;

	void remove_index_node (const Index_node* index);
	void remove_storage_node (const Storage_node* st);

	/*
	 * Whole graph.
	 */

	bool equals (Points_to_impl* other);
	void dump_graphviz (String* label, Context* cx, Result_state state, Whole_program* wp) const;

	Points_to_impl* clone() const;
	Points_to_impl* merge (Points_to_impl* other) const;

	void consistency_check (Context* cx, Result_state state, Whole_program* wp) const;


	static Index_node_list* get_possible_nulls (List<Points_to_impl*>* graphs);

	// A lot of points in the graph use names derived from some context. Change
	// them to use a non-contextual version.
	void convert_context_names ();

	void remove_unreachable_nodes ();

	/*
	 * Lower-level API
	 */

private:

	void remove_node (const Alias_name* node);

	reference_pair_type* merge_references (Points_to_impl* other) const;
};


/*
 * A thin wrapper around Points-to, to provide copy-on-write. There are
 * probably better ways to do this (ie reuse someone else's code), but they
 * rely on C++ idioms, which we haven't really been using.
 *
 * A Points_to_impl belongs to a Points_to, and is never passed directly to
 * another Points_to.
 */
class Points_to : virtual public GC_obj
{
private:
	Points_to_impl* impl;
	int reference_count;

	void detach ()
	{
		if (this->impl->reference_count == 1)
			return;

		impl = impl->clone ();
	}

	Points_to (Points_to_impl* impl)
	: impl (impl)
	{
	}


public:

	Points_to ()
	{
		impl = new Points_to_impl;
	}

	/*
	 * Simple pass-through
	 */

	bool has_field (const Index_node* field) const { return impl->has_field (field); };
	bool has_points_to (const Index_node* source, const Storage_node* target) const { return impl->has_points_to (source, target); }
	bool has_reference (const Index_node* source, const Index_node* target) const { return impl->has_reference (source, target); }
	bool has_reference (Reference_edge* edge) const { return impl->has_reference (edge); }
	bool has_storage_node (const Storage_node* st) const { return impl->has_storage_node (st); }
	bool is_abstract_field (const Index_node* index) const { return impl->is_abstract_field (index); }
	bool is_abstract (const Storage_node* st) const { return impl->is_abstract (st); }
	bool is_symtable (const Storage_node* st) const { return impl->is_symtable (st); }
	Certainty get_reference_cert (const Index_node* source, const Index_node* target) const { return impl->get_reference_cert (source, target); }
	Certainty get_reference_cert (Reference_edge* edge) const { return impl->get_reference_cert (edge); }
	cIndex_node_list* get_fields (const Storage_node* storage) const { return impl->get_fields (storage); }
	cIndex_node_list* get_index_nodes () const { return impl->get_index_nodes (); }
	cIndex_node_list* get_points_to_incoming (const Storage_node* st) const { return impl->get_points_to_incoming (st); }
	cAlias_name_list* get_nodes () const { return impl->get_nodes (); }
	cReference_list* get_references (const Index_node* source, Certainty cert = PTG_ALL) const { return impl->get_references (source, cert); }
	const Storage_node* get_owner (const Index_node* index) const { return impl->get_owner (index); }
	const Storage_node* get_storage (const Index_node* field) const { return impl->get_storage (field); }
	cIndex_node_list* get_incoming (const Storage_node* st) const { return impl->get_incoming (st); }
	cStorage_node_list* get_points_to (const Index_node* index) const { return impl->get_points_to (index); }
	cStorage_node_list* get_storage_nodes () const { return impl->get_storage_nodes (); }
	cField_edge_list* get_field_edges () const { return impl->get_field_edges ();	}
	cPoints_to_edge_list* get_points_to_edges () const { return impl->get_points_to_edges (); }
	cReference_edge_list* get_possible_reference_edges () const { return impl->get_possible_reference_edges (); }
	cReference_edge_list* get_definite_reference_edges () const { return impl->get_definite_reference_edges (); }
	void consistency_check (Context* cx, Result_state state, Whole_program* wp) const { return impl->consistency_check (cx, state, wp); }
	void dump_graphviz (String* label, Context* cx, Result_state state, Whole_program* wp) const { return impl->dump_graphviz (label, cx, state, wp); }

	/*
	 * Minor interfacing work involved
	 */
	static Index_node_list* get_possible_nulls (List<Points_to*>* graphs)
	{
		List<Points_to_impl*>* impls = new List<Points_to_impl*>;
		foreach (Points_to* ptg, *graphs)
		{
			impls->push_back (ptg->impl);
		}
		return Points_to_impl::get_possible_nulls (impls);
	}

	bool equals (Points_to* other) const
	{
		if (this->impl == other->impl)
			return true;

		return this->impl->equals (other->impl);
	}

	Points_to* clone () const
	{
		this->impl->reference_count++;
		return new Points_to (this->impl);
	}

	Points_to* merge (Points_to* other) const
	{
		if (this->impl == other->impl)
		{
			this->impl->reference_count++;
			return new Points_to (this->impl);
		}

		return new Points_to (this->impl->merge (other->impl));
	}



	/*
	 * Needs to clone for copy-on-write
	 */

	void open_scope (const Storage_node* st)
	{
		detach ();
		impl->open_scope (st);
	}

	void close_scope (const Storage_node* st)
	{
		detach ();
		impl->close_scope (st);
	}

	void inc_abstract (const Storage_node* st)
	{
		detach ();
		impl->inc_abstract (st);
	}

	void add_reference (const Index_node* source, const Index_node* target, Certainty cert)
	{
		detach ();
		impl->add_reference (source, target, cert);
	}

	void remove_reference (const Index_node* source, const Index_node* target)
	{
		detach ();
		impl->remove_reference (source, target);
	}

	void add_points_to (const Index_node* source, const Storage_node* target)
	{
		detach ();
		impl->add_points_to (source, target);
	}

	void remove_points_to (const Index_node* source, const Storage_node* target)
	{
		detach ();
		impl->remove_points_to (source, target);
	}

	void add_field (const Index_node* field)
	{
		detach ();
		impl->add_field (field);
	}

	void remove_field (const Index_node* target)
	{
		detach ();
		impl->remove_field (target);
	}

	void remove_index_node (const Index_node* index)
	{
		detach ();
		impl->remove_index_node (index);
	}

	void remove_storage_node (const Storage_node* st)
	{
		detach ();
		impl->remove_storage_node (st);
	}

	void convert_context_names ()
	{
		detach ();
		impl->convert_context_names ();
	}

	void remove_unreachable_nodes ()
	{
		detach ();
		impl->remove_unreachable_nodes ();
	}
};


#endif // PHC_POINTS_TO
