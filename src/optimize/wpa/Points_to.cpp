/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Points-to graph.
 *
 * There should be multiple graphs, 1 per function. there need to be links
 * between them, so I'm not clear if its better to have multiple regions
 * within a graph, or multiple graphs.
 *
 */

#include "MIR.h"
#include "lib/error.h"
#include "lib/escape.h"
#include "lib/demangle.h"
#include "process_ir/General.h"

#include "Points_to.h"
#include "Whole_program.h"
#include "optimize/Abstract_value.h"

using namespace MIR;
using namespace std;
using namespace boost;

Points_to_impl::Points_to_impl ()
: reference_count (1)
{
	// Pretend this is abstract so that it doesnt get removed.
	abstract_states [SN("_SESSION")] = Abstract_state::ABSTRACT;
	abstract_states [SN("FAKE")] = Abstract_state::ABSTRACT;
}

/*
 * Add a storage node for the scope (or it might exist already in the case of
 * recursion).
 */
void
Points_to_impl::open_scope (const Storage_node* st)
{
	symtables.insert (st);
}

void
Points_to_impl::inc_abstract (const Storage_node* st)
{
	abstract_states [st] = Abstract_state::inc (abstract_states [st]);
}

void
Points_to_impl::dec_abstract (const Storage_node* st)
{
	abstract_states [st] = Abstract_state::dec (abstract_states [st]);

	if (abstract_states [st] == Abstract_state::MISSING)
	{
		// Remove the symbol table. Then do a mark-and-sweep from all the other
		// symbol tables.
		remove_storage_node (st);
		remove_unreachable_nodes ();
	}
}

void
Points_to_impl::close_scope (const Storage_node* st)
{
	dec_abstract (st);
}

bool
Points_to_impl::is_abstract (const Storage_node* st) const
{
	// An abstract storage_node represents more than 1 real node. For example:
	//		an object instantiation
	//		implicit conversion
	//		array_creation
	//		symtable creation
	//		etc
	//
	//		in a loop
	//		multiple times in the (exact) same context
	//		etc
	//
	return abstract_states [st] == Abstract_state::ABSTRACT;
}

bool
Points_to_impl::is_abstract_field (const Index_node* index) const
{
	return is_abstract (get_owner (index));
}

bool
Points_to_impl::is_symtable (const Storage_node* st) const
{
	return symtables.has (st);
}


/*
 * References
 */

// Return a list of aliases which are references, and have the same certainty.
// INDEX is not included in the returned list.
cReference_list*
Points_to_impl::get_references (const Index_node* index, Certainty cert) const
{
	cReference_list* result = new cReference_list;
	foreach (const Index_node* target, *references.get_targets (index))
	{
		Certainty target_cert = references.get_value (index, target);
		if (cert & target_cert)
			result->push_back (new Reference (target, target_cert));
	}
	return result;
}

Certainty
Points_to_impl::get_reference_cert (const Index_node* source, const Index_node* target) const
{
	Certainty result = this->references.get_value (source, target);
	assert (is_valid_certainty (result));
	return result;
}

Certainty
Points_to_impl::get_reference_cert (const Reference_edge* edge) const
{
	return get_reference_cert (edge->source, edge->target);
}

void
Points_to_impl::add_reference (const Index_node* source, const Index_node* target, Certainty cert)
{
	assert (is_valid_certainty (cert));

	this->add_field (source);
	this->add_field (target);

	if (*source == *target)
		return;

	if (references.has_edge (source, target) and references.get_value (source, target) != cert)
		// TODO: check if there already is a CERT, and combine them (which way?).
    phc_optimization_exception ("Combining reference edges of different certainty unsupported");

	// These are always bidirectional.
	references.add_edge (source, target, cert);
	references.add_edge (target, source, cert);
}


bool
Points_to_impl::has_reference (const Reference_edge* edge) const
{
	return has_reference (edge->source, edge->target);
}

bool
Points_to_impl::has_reference (const Index_node* source, const Index_node* target) const
{
	return references.has_edge (source, target);
}

void
Points_to_impl::remove_reference (const Index_node* source, const Index_node* target)
{
	references.remove_edge (source, target);
	references.remove_edge (target, source);
}


/*
 * Points-to edges
 */

cStorage_node_list*
Points_to_impl::get_points_to (const Index_node* index) const
{
	return points_to.get_targets (index);
}

cIndex_node_list*
Points_to_impl::get_points_to_incoming (const Storage_node* st) const
{
	return points_to.get_sources (st);
}

void
Points_to_impl::add_points_to (const Index_node* index, const Storage_node* st)
{
	this->add_field (index);
	points_to.add_edge (index, st);
}

bool
Points_to_impl::has_points_to (const Index_node* index, const Storage_node* st) const
{
	return points_to.has_edge (index, st);
}

void
Points_to_impl::remove_points_to (const Index_node* index, const Storage_node* st)
{
	// If this has no remaining points-to edges, it should be redirected to
	// point-to NULL (or SCLVAL, whose value should be set to NULL). But its
	// very hard to do that here, so we shall assume that this is only done by a
	// caller.
	points_to.remove_edge (index, st);
}


/*
 * Field edges
 */

cIndex_node_list*
Points_to_impl::get_fields (const Storage_node* st) const
{
	return fields.get_targets (st);
}

void
Points_to_impl::add_field (const Index_node* index)
{
	fields.add_edge (SN (index->storage), index);
}

bool
Points_to_impl::has_field (const Index_node* index) const
{
	return fields.has_edge (SN (index->storage), index);
}

const Storage_node*
Points_to_impl::get_storage (const Index_node* index) const
{
	cStorage_node_list* storage = fields.get_sources (index);
	assert (storage->size () == 1);
	return storage->front ();
}


cIndex_node_list*
Points_to_impl::get_incoming (const Storage_node* st) const
{
	return points_to.get_sources (st);
}

const Storage_node*
Points_to_impl::get_owner (const Index_node* index) const
{
	// Simplest case: the first and node exist
	cStorage_node_list* storages = fields.get_sources (index);
	if (storages->size () == 1)
		return storages->front ();


	/*
	 * The rest are HACKs
	 */


	// With no colons in the same, its a storage node
	if (index->storage.find (':') == string::npos)
		return SN (index->storage);


	// It must be a value node
	return new Value_node (index->storage);
}

void
Points_to_impl::remove_field (const Index_node* index)
{
	fields.remove_edge (SN (index->storage), index);

	// Also remove any outgoing edges from index.
	references.remove_all_incoming_edges (index);
	references.remove_all_outgoing_edges (index);
	points_to.remove_all_outgoing_edges (index);
}



/*
 * Generic API (not specific to a particular edge type)
 */

bool
Points_to_impl::has_storage_node (const Storage_node* st) const
{
	return points_to.has_target (st) or fields.has_source (st);
}




/*
 * For working with the whole Points-to graph.
 */

bool
Points_to_impl::equals (Points_to_impl* other)
{
	return true
		&& this->fields.equals (&other->fields)
		&& this->points_to.equals (&other->points_to)
		&& this->references.equals (&other->references)
		&& this->abstract_states.equals (&other->abstract_states)
		&& this->symtables.equals (&other->symtables)
		;
}

template<class E>
string print_pair (E* edge, string label)
{
	stringstream ss;
	ss
	<< "\""
	<< *escape_DOT (s (edge->source->str())) 
	<< "\" -> \"" 
	<< *escape_DOT (s (edge->target->str())) 
	<< "\" [label=\"" << label << "\"];\n"
	;
	return ss.str ();
}


void
Points_to_impl::dump_graphviz (String* label, Context* cx, Result_state state, Whole_program* wp) const
{
	if (label == NULL)
	{
		CHECK_DEBUG ();
		label = s("TEST");
	}

	cout
	<< "digraph G {\n"
	<< "graph [labelloc=t];\n"
	<< "graph [label=\"Points-to: " << *label << "\"];\n"
	;

	// Add nodes
	foreach (const Alias_name* node, *this->get_nodes ())
	{
		cout
		<< "\""
		<< *escape_DOT (s (node->str ()))
		<< "\" ["
		;

		/*
		 * Label
		 */
		stringstream label;
		label
		<< "label=\""
		<< *escape_DOT (node->get_graphviz_label ())
		;
		
		if (isa<Value_node> (node))
		{
			stringstream cell_label;
			const Abstract_value* val = wp->get_abstract_value (cx, state, node);
			val->dump (cell_label);

			label
			<< *escape_DOT (s(cell_label.str()))
			;
		}

		label
		<< "\","
		;


		/*
		 * Color
		 */
		stringstream color;
		if (isa<Value_node> (node))
			color << "color=blue,";

		if (isa<Storage_node> (node) && is_abstract (dyc<Storage_node> (node)))
			color << "color=red,";

		if (isa<Storage_node> (node) && is_symtable (dyc<Storage_node> (node)))
			color << "style=filled,";

		/*
		 * Shape
		 */
		stringstream shape;
		if (isa<Storage_node> (node))
			shape << "shape=box,";

		/* Combine them all */
		cout
		<< label.str ()
		<< shape.str ()
		<< color.str ()
		;


		cout << "];\n" ;
	}

	// Add edges
	foreach (const Reference_edge* edge, *references.get_edges ())
		cout << print_pair (edge, (references.get_value (edge) == POSSIBLE ? "P" : "D"));

	foreach (const Field_edge* edge, *fields.get_edges ())
		cout << print_pair (edge, "");

	foreach (const Points_to_edge* edge, *points_to.get_edges ())
		cout << print_pair (edge, "");

	cout
	<< "}\n"
	;
}

Points_to_impl*
Points_to_impl::clone () const
{
	Points_to_impl* result = new Points_to_impl;

	// Deep copy
	result->symtables = this->symtables;
	result->abstract_states = this->abstract_states;

	// These will copy pointers to nodes. But that's OK, since nodes are never
	// updated.
	result->references = this->references;
	result->points_to = this->points_to;
	result->fields = this->fields;

	return result;
}

void
Points_to_impl::consistency_check (Context* cx, Result_state state, Whole_program* wp) const
{
	foreach (const Index_node* index, *this->get_index_nodes ())
	{
		// Check index nodes are pointed to by their storage node
		if (not this->has_field (index))
		{
			dump_graphviz (NULL, cx, state, wp);
			phc_internal_error ("No field-edge to %s",
					index->str().c_str());
		}

		// Check every index node points_to something.
		if (this->get_points_to (index)->size () == 0)
		{
			dump_graphviz (NULL, cx, state, wp);
			phc_internal_error ("No points-to edge from %s",
					index->str().c_str());
		}

		if (isa<Value_node> (this->get_storage (index)))
		{
			dump_graphviz (NULL, cx, state, wp);
			phc_internal_error ("Abstract values can't have fields %s",
					index->str().c_str());
		}
	}

	foreach (const Reference_edge* ref_edge, *this->references.get_edges ())
	{
		Certainty cert = this->references.get_value (ref_edge);
		if (not is_valid_certainty (cert))
		{
			dump_graphviz (NULL, cx, state, wp);
			phc_internal_error ("Certs can't be %d between %s and %s",
					cert,
					ref_edge->source->str().c_str(),
					ref_edge->target->str().c_str());
		}
	}
}





cIndex_node_list*
Points_to_impl::get_index_nodes () const
{
	return filter_types <const Index_node> (this->get_nodes ());
}


cStorage_node_list*
Points_to_impl::get_storage_nodes () const
{
	return filter_types <const Storage_node> (this->get_nodes ());
}


cField_edge_list* 
Points_to_impl::get_field_edges () const
{
	return fields.get_edges (); 
}

cPoints_to_edge_list*
Points_to_impl::get_points_to_edges () const
{
	return points_to.get_edges ();
}

cReference_edge_list*
Points_to_impl::get_possible_reference_edges () const
{
	cReference_edge_list* result = new cReference_edge_list ();
	
	foreach (const Reference_edge* refedge, *references.get_edges ())
	{
		if (references.get_value (refedge) == POSSIBLE)
			result->push_back (refedge);
	}
	
	return result;
}

cReference_edge_list*
Points_to_impl::get_definite_reference_edges () const
{
	cReference_edge_list* result = new cReference_edge_list ();
	
	foreach (const Reference_edge* refedge, *references.get_edges ())
	{
		if (references.get_value (refedge) == DEFINITE)
			result->push_back (refedge);
	}
	
	return result;
}


// Mark all symtable nodes, then sweep anything they can reach. Remove the
// rest.
void
Points_to_impl::remove_unreachable_nodes ()
{
	cAlias_name_list* worklist = new cAlias_name_list;

	// Put all symtables into the worklist
	foreach (const Storage_node* st, *this->get_storage_nodes ())
	{
		if (this->is_symtable (st) || is_abstract (st))
			worklist->push_back (st);
	}

	// Mark all reachable nodes
	Set<const Alias_name*> reachable;
	while (worklist->size () > 0)
	{
		const Alias_name* node = worklist->front ();
		worklist->pop_front ();

		if (reachable.has (node))
			continue;

		// Mark reachable
		reachable.insert (node);

		// Fetch the targets
		if (isa<Storage_node> (node))
		{
			cIndex_node_list* fields = this->get_fields (dyc<Storage_node> (node)); 
			worklist->push_back_all (rewrap_list<const Alias_name, const Index_node> (fields));
		}
		else
		{
			// Dont follow reference edges (not necessary cause of transitive-closure)
			cStorage_node_list* points_to = this->get_points_to (dyc<Index_node> (node)); 
			worklist->push_back_all (rewrap_list<const Alias_name, const Storage_node> (points_to));
		}
	}

	// remove all nodes not marked as reachable
	foreach (const Alias_name* node, *this->get_nodes ())
	{
		if (!reachable.has (node))
		{
			this->remove_node (node);
		}
	}
}


/*
 * Low-level API
 */

void
Points_to_impl::remove_node (const Alias_name* node)
{
	if (isa<Index_node> (node))
		this->remove_field (dyc<Index_node> (node));
	else
		this->remove_storage_node (dyc<Storage_node> (node));
}

Points_to_impl::reference_pair_type*
Points_to_impl::merge_references (Points_to_impl* other) const
{
	reference_pair_type* result = this->references.merge (&other->references);

	// Given two graphs, with A->B on G1, and B->C in G2, we don't need to ensure that
	// A->C is added too.
	

	foreach (const Reference_edge* edge, *result->get_edges ())
	{
		bool this_has = this->has_reference (edge);
		bool other_has = other->has_reference (edge);

		if (this_has and other_has)
		{
			Certainty this_cert = this->get_reference_cert (edge);
			Certainty other_cert = other->get_reference_cert (edge);
			result->set_value (edge, combine_certs (this_cert, other_cert));
		}
		else 
		{
			assert (this_has or other_has);
			result->set_value (edge, POSSIBLE);
		}
	}

	return result;
}


/*
 * Merge another graph with this one. Edge cases with NULL are handled in
 * Whole_program, using get_possible_nulls().
 */
Points_to_impl*
Points_to_impl::merge (Points_to_impl* other) const
{
	Points_to_impl* result = new Points_to_impl;

	result->fields = *this->fields.merge (&other->fields);
	result->points_to = *this->points_to.merge (&other->points_to);
	result->references = *this->merge_references (other);

	// Combine the abstract counts
	result->abstract_states = this->abstract_states;

	// For counts in OTHER, use the max (for counts only in OTHER, OTHER's
	// version will be used).
	const Storage_node* name;
	Abstract_state::AS state;
	foreach (tie (name, state), other->abstract_states)
		result->abstract_states [name] = Abstract_state::merge (state, other->abstract_states [name]);


	// Combine the list of symtables
	result->symtables = *this->symtables.set_union (&other->symtables);

	return result;
}

cAlias_name_list*
Points_to_impl::get_nodes () const
{
	// Only have the nodes once
	Set<const Alias_name*> all;

	foreach (const Reference_edge* edge, *this->references.get_edges ())
	{
		all.insert (edge->source);
		all.insert (edge->target);
	}

	foreach (const Field_edge* edge, *this->fields.get_edges ())
	{
		all.insert (edge->source);
		all.insert (edge->target);
	}

	foreach (const Points_to_edge* edge, *this->points_to.get_edges ())
	{
		all.insert (edge->source);
		all.insert (edge->target);
	}

	List<const Storage_node*>* storages = abstract_states.keys ();
	all.insert (storages->begin (), storages->end ());
	all.insert (symtables.begin (), symtables.end ());

	return all.to_list ();
}


void
Points_to_impl::remove_storage_node (const Storage_node* st)
{
	foreach (const Index_node* field, *this->get_fields (st))
	{
		remove_field (field);
	}

	symtables.erase (st);
	abstract_states.erase (st);
}

/*
 * Dealing with the context name HACK
 */
void
Points_to_impl::convert_context_names ()
{
	// Each alias_name can be converted in either the prefix or the suffix.
	// By_source and by_target need to be updated.

	// Merging storage nodes:
	//		Symtables definitely need to be merged.
	//		There are pros and cons to merging Objects and arrays:
	//			- We might like to distinguish between them
	//			- We might like to have a single node representing an allocation
	//			- If we dont merge them, we're still merging the LHS of the
	//			  allocation, so $x = new X will have $x pointing to multiple X
	//			  nodes.
	//
	//	So just merge them all, until there is a good reason not to.

	fields = *fields.convert_context_names ();
	references = *references.convert_context_names ();
	points_to = *points_to.convert_context_names ();


	// Convert symtable names
	Set<const Storage_node*> old_symtables = this->symtables;
	this->symtables.clear ();
	foreach (const Storage_node* name, old_symtables)
	{
		this->symtables.insert (name->convert_context_name ());
	}

	// Convert abstract counts
	// I'm not really sure what to do here.
	const Storage_node* name;
	Abstract_state::AS state;
	Map<const Storage_node*, Abstract_state::AS> old_abstract_states = this->abstract_states;
	this->abstract_states.clear ();
	foreach (tie (name, state), old_abstract_states)
	{
		const Storage_node* converted = name->convert_context_name ();
		abstract_states[converted] = Abstract_state::merge (state, abstract_states[converted]);
	}
}


	
/*
 * Nodes
 */
Storage_node*
SN (string scope)
{
	return new Storage_node (scope);
}

Index_node*
IN (string scope, string name)
{
	return new Index_node (scope, name);
}

Index_node*
VN (string scope, MIR::VARIABLE_NAME* var)
{
	return IN (scope, *var->value);
}

Index_node*
FN (string scope, MIR::FIELD_NAME* field)
{
	return IN (scope, *field->value);
}

Value_node*
SCLVAL (const Index_node* node)
{
	return new Value_node (node);
}


/*
 * Storage node
 */

Storage_node::Storage_node (string storage)
: storage (storage)
{
	assert (storage != "");
}

string
Storage_node::str () const
{
	return string(SNP) + "::" + storage;
}

String*
Storage_node::get_graphviz_label () const
{
	return s(storage);
}

Storage_node*
Storage_node::convert_context_name () const
{
	return SN (Context::convert_context_name (storage));
}




/*
 * Index node
 */

Index_node::Index_node (string storage, string index)
: storage (storage)
, index (index)
{
	assert (storage != "");
}

string
Index_node::str () const
{
	return this->storage + "::" + this->index;
}

Index_node*
Index_node::get_starred_name () const
{
	return new Index_node ("*_" + this->storage, this->index);
}

bool Index_node::is_starred() const {
	return boost::starts_with(this->storage, "*_");
}

String*
Index_node::get_graphviz_label () const
{
	return s(index);
}

Index_node*
Index_node::convert_context_name () const
{
	return new Index_node (
		Context::convert_context_name (storage),
		Context::convert_context_name (index));
}

/*
 * Value node
 */

Value_node::Value_node (const Index_node* owner)
: Storage_node (owner->str())
{
	assert (storage != "");
}

string
Value_node::str () const
{
	return storage + "::" + SCL;
}

Value_node::Value_node (string owner)
: Storage_node (owner)
{
	assert (storage != "");
}

String*
Value_node::get_graphviz_label () const
{
	return s("");
}

Value_node*
Value_node::convert_context_name () const
{
	return new Value_node (Context::convert_context_name (storage));
}



/*
 * Abstract_states
 */

namespace Abstract_state
{
	AS inc (AS as)
	{
		if (as == MISSING)
			return PRESENT;
		else
			return ABSTRACT;
	}

	AS dec (AS as)
	{
		assert (as != MISSING);
		if (as == PRESENT)
			return MISSING;
		else
			return ABSTRACT;
	}

	AS merge (AS as1, AS as2)
	{
		if (as1 == ABSTRACT || as2 == ABSTRACT)
			return ABSTRACT;
		else if (as1 == PRESENT || as2 == PRESENT)
			return PRESENT;
		else
			return MISSING;
	}
}
