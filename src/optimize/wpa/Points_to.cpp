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
	abstract_states [SN("_SESSION")->name()] = Abstract_state::ABSTRACT;
	abstract_states [SN("FAKE")->name()] = Abstract_state::ABSTRACT;
}

/*
 * Add a storage node for the scope (or it might exist already in the case of
 * recursion).
 */
void
Points_to_impl::open_scope (Storage_node* st)
{
	symtables.insert (st->name ());
}

void
Points_to_impl::inc_abstract (Storage_node* st)
{
	Alias_name name = st->name ();
	abstract_states [name] = Abstract_state::inc (abstract_states [name]);
}

void
Points_to_impl::dec_abstract (Storage_node* st)
{
	Alias_name name = st->name ();
	abstract_states [name] = Abstract_state::dec (abstract_states [name]);

	if (abstract_states [name] == Abstract_state::MISSING)
	{
		// Remove the symbol table. Then do a mark-and-sweep from all the other
		// symbol tables.
		remove_storage_node (st);
		remove_unreachable_nodes ();
	}
}

void
Points_to_impl::close_scope (Storage_node* st)
{
	dec_abstract (st);
}

bool
Points_to_impl::is_abstract (Storage_node* st)
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
	return abstract_states [st->name()] == Abstract_state::ABSTRACT;
}

bool
Points_to_impl::is_abstract_field (Index_node* index)
{
	return is_abstract (get_owner (index));
}

bool
Points_to_impl::is_symtable (Storage_node* st)
{
	return symtables.has (st->name ());
}


/*
 * References
 */

// Return a list of aliases which are references, and have the same certainty.
// INDEX is not included in the returned list.
Reference_list*
Points_to_impl::get_references (Index_node* index, Certainty cert)
{
	Reference_list* result = new Reference_list;
	foreach (Index_node* target, *references.get_targets (index))
	{
		Certainty target_cert = references.get_value (index, target);
		if (cert & target_cert)
			result->push_back (new Reference (target, target_cert));
	}
	return result;
}

Certainty
Points_to_impl::get_reference_cert (Index_node* source, Index_node* target)
{
	Certainty result = this->references.get_value (source, target);
	assert (is_valid_certainty (result));
	return result;
}

Certainty
Points_to_impl::get_reference_cert (Reference_edge* edge)
{
	return get_reference_cert (edge->source, edge->target);
}

void
Points_to_impl::add_reference (Index_node* source, Index_node* target, Certainty cert)
{
	assert (is_valid_certainty (cert));

	this->add_field (source);
	this->add_field (target);

	if (references.has_edge (source, target) and references.get_value (source, target) != cert)
		phc_TODO (); // check if there already is a CERT, and combine them (which way?).

	// These are always bidirectional.
	references.add_edge (source, target);
	references.add_edge (target, source);
	references.set_value (source, target, cert);
	references.set_value (target, source, cert);
}


bool
Points_to_impl::has_reference (Reference_edge* edge)
{
	return has_reference (edge->source, edge->target);
}

bool
Points_to_impl::has_reference (Index_node* source, Index_node* target)
{
	return references.has_edge (source, target);
}

void
Points_to_impl::remove_reference (Index_node* source, Index_node* target)
{
	references.remove_edge (source, target);
	references.remove_edge (target, source);
}


/*
 * Points-to edges
 */

Storage_node_list*
Points_to_impl::get_points_to (Index_node* index)
{
	return points_to.get_targets (index);
}

Index_node_list*
Points_to_impl::get_points_to_incoming (Storage_node* st)
{
	return points_to.get_sources (st);
}

void
Points_to_impl::add_points_to (Index_node* index, Storage_node* st)
{
	this->add_field (index);
	points_to.add_edge (index, st);
}

bool
Points_to_impl::has_points_to (Index_node* index, Storage_node* st)
{
	return points_to.has_edge (index, st);
}

void
Points_to_impl::remove_points_to (Index_node* index, Storage_node* st)
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

Index_node_list*
Points_to_impl::get_fields (Storage_node* st)
{
	return fields.get_targets (st);
}

void
Points_to_impl::add_field (Index_node* index)
{
	fields.add_edge (SN (index->storage), index);
}

bool
Points_to_impl::has_field (Index_node* index)
{
	return fields.has_edge (SN (index->storage), index);
}

Storage_node*
Points_to_impl::get_storage (Index_node* index)
{
	Storage_node_list* storage = fields.get_sources (index);
	assert (storage->size () == 1);
	return storage->front ();
}

Storage_node*
Points_to_impl::get_owner (Index_node* index)
{
	// Simplest case: the first and node exist
	Storage_node_list* storages = fields.get_sources (index);
	if (storages->size () == 1)
		return storages->front ();


	/*
	 * The rest are HACKs
	 */


	// With no colons in the same, its a storage node
	if (index->storage.find (':') == string::npos)
		return SN (index->storage);


	// If it ends in ::SCL, its a value node
	if (index->storage.find ("::SCL") == index->storage.size () - 5)
	{
		string new_name = index->storage.substr (0, index->storage.size () - 5);
		return new Value_node (new_name);
	}


	phc_TODO ();
}

void
Points_to_impl::remove_field (Index_node* index)
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
Points_to_impl::has_storage_node (Storage_node* st)
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
	<< *escape_DOT (s (edge->source->name ().str())) 
	<< "\" -> \"" 
	<< *escape_DOT (s (edge->target->name ().str())) 
	<< "\" [label=\"" << label << "\"];\n"
	;
	return ss.str ();
}


void
Points_to_impl::dump_graphviz (String* label, Context* cx, Result_state state, Whole_program* wp)
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
	foreach (PT_node* node, *get_nodes ())
	{
		cout
		<< "\""
		<< *escape_DOT (s (node->name().str ()))
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
			Abstract_value* val = wp->get_abstract_value (cx, state, node->name ());
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
	foreach (Reference_edge* edge, *references.get_edges ())
		cout << print_pair (edge, (references.get_value (edge) == POSSIBLE ? "P" : "D"));

	foreach (Field_edge* edge, *fields.get_edges ())
		cout << print_pair (edge, "");

	foreach (Points_to_edge* edge, *points_to.get_edges ())
		cout << print_pair (edge, "");

	cout
	<< "}\n"
	;
}

Points_to_impl*
Points_to_impl::clone ()
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
Points_to_impl::consistency_check (Context* cx, Result_state state, Whole_program* wp)
{
	foreach (Index_node* index, *this->get_index_nodes ())
	{

		// Check index nodes are pointed to by their storage node
		if (not this->has_field (index))
		{
			dump_graphviz (NULL, cx, state, wp);
			phc_internal_error ("No field-edge to %s",
					index->name().str().c_str());
		}

		// Check every index node points_to something.
		if (this->get_points_to (index)->size () == 0)
		{
			dump_graphviz (NULL, cx, state, wp);
			phc_internal_error ("No points-to edge from %s",
					index->name().str().c_str());
		}

		if (isa<Value_node> (this->get_storage (index)))
		{
			dump_graphviz (NULL, cx, state, wp);
			phc_internal_error ("Abstract values can't have fields %s",
					index->name().str().c_str());
		}
	}

	foreach (Reference_edge* ref_edge, *this->references.get_edges ())
	{
		Certainty cert = this->references.get_value (ref_edge);
		if (not is_valid_certainty (cert))
		{
			dump_graphviz (NULL, cx, state, wp);
			phc_internal_error ("Certs can't be %d between %s and %s",
					cert,
					ref_edge->source->name().str().c_str(),
					ref_edge->target->name().str().c_str());
		}
	}
}





Index_node_list*
Points_to_impl::get_index_nodes ()
{
	return filter_types <Index_node> (this->get_nodes ());
}


Storage_node_list*
Points_to_impl::get_storage_nodes ()
{
	return filter_types <Storage_node> (this->get_nodes ());
}



// Mark all symtable nodes, then sweep anything they can reach. Remove the
// rest.
void
Points_to_impl::remove_unreachable_nodes ()
{
	PT_node_list* worklist = new PT_node_list;

	// Put all symtables into the worklist
	foreach (Storage_node* st, *this->get_storage_nodes ())
	{
		if (this->is_symtable (st) || is_abstract (st))
			worklist->push_back (st);
	}

	// Mark all reachable nodes
	Set<Alias_name> reachable;
	while (worklist->size () > 0)
	{
		PT_node* node = worklist->front ();
		worklist->pop_front ();

		if (reachable.has (node->name ()))
			continue;

		// Mark reachable
		reachable.insert (node->name ());

		// Fetch the targets
		if (isa<Storage_node> (node))
		{
			Index_node_list* fields = this->get_fields (dyc<Storage_node> (node)); 
			worklist->push_back_all (rewrap_list<PT_node, Index_node> (fields));
		}
		else
		{
			// Dont follow reference edges (not necessary cause of transitive-closure)
			Storage_node_list* points_to = this->get_points_to (dyc<Index_node> (node)); 
			worklist->push_back_all (rewrap_list<PT_node, Storage_node> (points_to));
		}
	}

	// remove all nodes not marked as reachable
	foreach (PT_node* node, *this->get_nodes ())
	{
		if (!reachable.has (node->name ()))
		{
			this->remove_node (node);
		}
	}
}


/*
 * Low-level API
 */

void
Points_to_impl::remove_node (PT_node* node)
{
	if (isa<Index_node> (node))
		this->remove_field (dyc<Index_node> (node));
	else
		this->remove_storage_node (dyc<Storage_node> (node));
}

Points_to_impl::reference_pair_type*
Points_to_impl::merge_references (Points_to_impl* other)
{
	reference_pair_type* result = this->references.merge (&other->references);

	// Given two graphs, with A->B on G1, and B->C in G2, we don't need to ensure that
	// A->C is added too.
	

	foreach (Reference_edge* edge, *result->get_edges ())
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
Points_to_impl::merge (Points_to_impl* other)
{
	Points_to_impl* result = new Points_to_impl;

	result->fields = *this->fields.merge (&other->fields);
	result->points_to = *this->points_to.merge (&other->points_to);
	result->references = *this->merge_references (other);

	// Combine the abstract counts
	result->abstract_states = this->abstract_states;

	// For counts in OTHER, use the max (for counts only in OTHER, OTHER's
	// version will be used).
	Alias_name name;
	Abstract_state::AS state;
	foreach (tie (name, state), other->abstract_states)
		result->abstract_states [name] = Abstract_state::merge (state, other->abstract_states [name]);


	// Combine the list of symtables
	result->symtables = *this->symtables.set_union (&other->symtables);

	return result;
}

PT_node_list*
Points_to_impl::get_nodes ()
{
	// Only have the nodes once
	Map<Alias_name, PT_node*> all;

	foreach (Reference_edge* edge, *this->references.get_edges ())
	{
		all[edge->source->name ()] = edge->source;
		all[edge->target->name ()] = edge->target;
	}

	foreach (Field_edge* edge, *this->fields.get_edges ())
	{
		all[edge->source->name ()] = edge->source;
		all[edge->target->name ()] = edge->target;
	}

	foreach (Points_to_edge* edge, *this->points_to.get_edges ())
	{
		all[edge->source->name ()] = edge->source;
		all[edge->target->name ()] = edge->target;
	}

	List<Alias_name>* storages = abstract_states.keys ();
	storages->push_back_all (symtables.to_list ());
	foreach (Alias_name storage, *storages)
	{
		if (not all.has (storage))
		{
			if (storage.name == "SCL")
				all[storage] = new Value_node (storage.prefix);
			else
				all[storage] = new Storage_node (storage.name);
		}
	}

	return all.values();
}


void
Points_to_impl::remove_storage_node (Storage_node* st)
{
	foreach (Index_node* field, *this->get_fields (st))
	{
		remove_field (field);
	}

	symtables.erase (st->name ());
	abstract_states.erase (st->name ());
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

	// Save the old alias pairs
	fields.convert_context_names ();
	references.convert_context_names ();
	points_to.convert_context_names ();


	// Convert symtable names
	Set<Alias_name> old_symtables = this->symtables;
	this->symtables.clear ();
	foreach (Alias_name name, old_symtables)
	{
		this->symtables.insert (name.convert_context_name ());
	}

	// Convert abstract counts
	// I'm not really sure what to do here.
	Alias_name name;
	Abstract_state::AS state;
	Map<Alias_name, Abstract_state::AS> old_abstract_states = this->abstract_states;
	this->abstract_states.clear ();
	foreach (tie (name, state), old_abstract_states)
	{
		Alias_name converted = name.convert_context_name ();
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
SCLVAL (Index_node* node)
{
	// we dont want to do this on an alias_name, or it'll be difficult.
	return new Value_node (node);
}



Storage_node::Storage_node (string storage)
: storage (storage)
{
	assert (storage != "");
}

Alias_name
Storage_node::name ()
{
	return Alias_name (SNP, storage);
}

String*
Storage_node::get_graphviz_label ()
{
	return s(storage);
}


Index_node::Index_node (string storage, string index)
: storage (storage)
, index (index)
{
	assert (storage != "");

	// An index can be "", but this can be caused by an error in the analyses.
	// However, its starting to come up in test code, so we should disable the
	// assertion.
//	assert (index != "");
}

Alias_name
Index_node::name ()
{
	return Alias_name (storage, index);
}

String*
Index_node::get_graphviz_label ()
{
	return s(index);
}

Value_node::Value_node (Index_node* owner)
: Storage_node (owner->name().str())
{
	assert (storage != "");
}

Value_node::Value_node (string owner)
: Storage_node (owner)
{
	assert (storage != "");
}

Alias_name
Value_node::name ()
{
	return Alias_name (storage, SCL);
}

String*
Value_node::get_graphviz_label ()
{
	return s("");
}



Index_node*
Index_node::convert_context_name ()
{
	return new Index_node (
		Context::convert_context_name (storage),
		Context::convert_context_name (index));
}


Storage_node*
Storage_node::convert_context_name ()
{
	return new Storage_node (
		Context::convert_context_name (storage));
}


Value_node*
Value_node::convert_context_name ()
{
	return new Value_node (Context::convert_context_name (storage));
}

string
Storage_node::for_index_node ()
{
	return this->storage;
}

string
Value_node::for_index_node ()
{
	return this->name().str ();
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
