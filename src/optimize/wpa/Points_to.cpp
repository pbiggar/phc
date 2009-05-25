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

Points_to::Points_to ()
{
	// Pretend this is a symtable so that it doesnt get removed.
	abstract_counts [SN("_SESSION")->name()]++;
}

/*
 * Add a storage node for the scope (or it might exist already in the case of
 * recursion).
 */
void
Points_to::open_scope (Storage_node* st)
{
	Alias_name name = st->name ();
	abstract_counts [name]++;
	symtables.insert (name);
}

void
Points_to::close_scope (Storage_node* st)
{
	Alias_name name = st->name ();
	abstract_counts [name]--;

	if (abstract_counts [name] == 0)
	{
		symtables.erase (name);
		abstract_counts.erase (name);

		// Remove the symbol table. Then do a mark-and-sweep from all the other
		// symbol tables.
		remove_storage_node (st);
		remove_unreachable_nodes ();
	}

	assert (abstract_counts [name] >= 0);
}

bool
Points_to::is_abstract (Storage_node* st)
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
	return abstract_counts [st->name()] > 1;
}

bool
Points_to::is_abstract_field (Index_node* index)
{
	return is_abstract (index->get_owner ());
}

bool
Points_to::is_symtable (Storage_node* st)
{
	return symtables.has (st->name ());
}


/*
 * References
 */

// Return a list of aliases which are references, and have the same certainty.
// INDEX is not included in the returned list.
Reference_list*
Points_to::get_references (Index_node* index, Certainty cert)
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

void
Points_to::set_reference_cert (Reference_edge* pair, Certainty cert)
{
	references.set_value (pair, cert);
}

void
Points_to::add_reference (Index_node* source, Index_node* target, Certainty cert)
{
	this->add_field (source);
	this->add_field (target);

	if (references.has_edge (source, target) and references.get_value (source, target) != cert)
		phc_TODO (); // check if there already is a CERT, and combine them (which way?).

	references.add_edge (source, target);
	set_reference_cert (new Reference_edge (source, target), cert);
}

bool
Points_to::has_reference (Index_node* source, Index_node* target)
{
	return references.has_edge (source, target);
}

void
Points_to::remove_reference (Index_node* source, Index_node* target)
{
	references.remove_edge (source, target);
}


/*
 * Points-to edges
 */

Storage_node_list*
Points_to::get_points_to (Index_node* index)
{
	return points_to.get_targets (index);
}

Index_node_list*
Points_to::get_points_to_incoming (Storage_node* st)
{
	return points_to.get_sources (st);
}

void
Points_to::add_points_to (Index_node* index, Storage_node* st)
{
	this->add_field (index);
	points_to.add_edge (index, st);
}

bool
Points_to::has_points_to (Index_node* index, Storage_node* st)
{
	return points_to.has_edge (index, st);
}

void
Points_to::remove_points_to (Index_node* index, Storage_node* st)
{
	// If this has no remaining points-to edges, it should be redirected to
	// point-to NULL (or ABSVAL, whose value should be set yo NULL). But its
	// very hard to do that here, so we shall assume that this is only done by a
	// caller.
	points_to.remove_edge (index, st);
}


/*
 * Field edges
 */

Index_node_list*
Points_to::get_fields (Storage_node* st)
{
	return fields.get_targets (st);
}

void
Points_to::add_field (Index_node* index)
{
	fields.add_edge (SN (index->storage), index);
}

bool
Points_to::has_field (Index_node* index)
{
	return fields.has_edge (SN (index->storage), index);
}

void
Points_to::remove_field (Index_node* index)
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
Points_to::has_storage_node (Storage_node* st)
{
	return points_to.has_target (st) or fields.has_source (st);
}




/*
 * For working with the whole Points-to graph.
 */

bool
Points_to::equals (Points_to* other)
{
	return true
		&& this->fields.equals (&other->fields)
		&& this->points_to.equals (&other->points_to)
		&& this->references.equals (&other->references)
		&& this->abstract_counts.equals (&other->abstract_counts)
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
Points_to::dump_graphviz (String* label, Context cx, Whole_program* wp)
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
		stringstream label, cell_label;
		label
		<< "label=\""
		<< *escape_DOT (node->get_graphviz_label ())
		;
		
		if (isa<Value_node> (node))
		{
			Abstract_value* val = wp->get_bb_out_abstract_value (cx, node->name());

			if (val->lit == BOTTOM)
				cell_label << "(B)";
			else if (val->lit == TOP)
				cell_label << "(T)";
			else
				dump_cell(val->lit, cell_label);

			cell_label << ", ";

			if (val->type == BOTTOM)
				cell_label << "(B)";
			else if (val->type == TOP)
				cell_label << "(T)";
			else
				dump_cell(val->type, cell_label);
		}
		label
		<< *escape_DOT (s(cell_label.str()))
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

Points_to*
Points_to::clone ()
{
	Points_to* result = new Points_to;

	// Deep copy
	result->symtables = this->symtables;
	result->abstract_counts = this->abstract_counts;

	// These will copy pointers to nodes. But that's OK, since nodes are never
	// updated.
	result->references = this->references;
	result->points_to = this->points_to;
	result->fields = this->fields;

	return result;
}

void
Points_to::consistency_check (Context cx, Whole_program* wp)
{
	phc_TODO ();
	/*
	 * TODO:
			// Check index nodes are pointed to by their storage node
				dump_graphviz (NULL, cx, wp);
				phc_internal_error ("No edge from storage node for %s",
										  ind->name().str().c_str());


			// Check there isnt > 1 DEFINITE reference
				dump_graphviz (NULL, cx, wp);
				phc_internal_error (
						"Multiple edges from %s, but edge to %s is DEFINITE",
						ind->name().str().c_str(),
						st->name().str().c_str());
	*/
}








Storage_node_list*
Points_to::get_storage_nodes ()
{
	Storage_node_list* result = new Storage_node_list;

	foreach (PT_node* node, *this->get_nodes ())
	{
		if (isa<Storage_node> (node))
			result->push_back (dyc<Storage_node> (node));
	}

	return result;
	
}



// Mark all symtable nodes, then sweep anything they can reach. Remove the
// rest.
void
Points_to::remove_unreachable_nodes ()
{
	// Summary: when removing a storage, remove all its index nodes.
	
	// Put all symtables into the worklist
	PT_node_list* worklist = new PT_node_list;
	PT_node_list* all_nodes = this->get_nodes ();
	foreach (PT_node* node, *all_nodes)
	{
		if (Storage_node* sn = dynamic_cast<Storage_node*> (node))
			worklist->push_back (sn);
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
	foreach (PT_node* node, *all_nodes)
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
Points_to::remove_node (PT_node* node)
{
	if (isa<Index_node> (node))
		this->remove_field (dyc<Index_node> (node));
	else
		this->remove_storage_node (dyc<Storage_node> (node));
}



/*
 * Given a list of points_to graphs, return the list of index_nodes which
 * might be NULL. An index node is in this set if the its storage node exists
 * in a graph in which it does not appear.
 */
Index_node_list*
Points_to::get_possible_nulls (List<Points_to*>* graphs)
{
	Index_node_list* result = new Index_node_list;

	Set<Alias_name> existing;

	// Foreach storage node S in G, check all other graphs for G. If they have
	// S, check for each I, such that S->I.
	foreach (Points_to* graph, *graphs)
	{
		foreach (Storage_node* st, *graph->get_storage_nodes ())
		{
			foreach (Index_node* index, *graph->get_fields (st))
			{
				// Check all the other graphs
				foreach (Points_to* other, *graphs)
				{
					if (graph == other)
						continue;

					if (other->has_storage_node (st) && !other->has_field (index))
					{
						// Add it
						if (!existing.has (index->name()))
						{
							existing.insert (index->name ());
							result->push_back (index);
						}
					}
				}
			}
		}
	}

	return result;
}

/*
 * Merge another graph with this one. Edge cases with NULL are handled in
 * Whole_program, using get_possible_nulls().
 */
Points_to*
Points_to::merge (Points_to* other)
{
	phc_TODO ();
	/*
	Points_to* result = new Points_to;

	// All edges from THIS.
	foreach (Alias_pair* p, this->all_pairs)
	{
		Alias_pair* other_pair = other->get_edge (p->source, p->target);
		// If the pair is in both graphs, add it with the combined CERT.
		if (other_pair)
		{
			result->add_edge (p->source, p->target,
				combine_certs (other_pair->cert, p->cert));
		}
		else
		{
			if (other->has_node (p->source) 
				&& isa<Index_node> (p->source) && isa<Index_node> (p->target))
			{
				// If the source node is in both graphs, but the edge is not,
				// then the edge becomes possible. This only applies to reference
				// edges (index->index), as we handle the NULL possabilities in
				// Whole_program.
				result->add_edge (p->source, p->target, POSSIBLE);
			}
			else
			{
				// If the source node is only in one graph, then the edge takes
				// its certainty from the current graph. 
				result->add_edge (p->source, p->target, p->cert);
			}
		}
	}

	// Add edges that are only in OTHER
	foreach (Alias_pair* p, other->all_pairs)
	{
		if (this->get_edge (p->source, p->target) == NULL)
		{
			if (this->has_node (p->source)
				&& isa<Index_node> (p->source) && isa<Index_node> (p->target))
			{
				// see above
				result->add_edge (p->source, p->target, POSSIBLE);
			}
			else
			{
				result->add_edge (p->source, p->target, p->cert);
			}
		}
	}

	// Combine the symtable records
	result->abstract_counts = this->abstract_counts;
	result->symtables = this->symtables;

	// For counts in OTHER, use the max (for counts only in OTHER, OTHER's
	// version will be used).
	Alias_name name;
	int count;
	foreach (tie (name, count), other->abstract_counts)
	{
		result->abstract_counts [name] = max (count,  other->abstract_counts [name]);
	}


	return result;
	*/
}

PT_node_list*
Points_to::get_nodes ()
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

	return all.values();
}


void
Points_to::remove_storage_node (Storage_node* st)
{
	// No node should point to it (assuming its a symtable).
	assert (this->get_points_to_incoming (st)->empty ());	

	foreach (Index_node* field, *this->get_fields (st))
	{
		remove_field (field);
	}
}

/*
 * Dealing with the context name HACK
 */
void
Points_to::convert_context_names ()
{
	// TODO: check that this creates new Index_nodes, as the pointers are shared
	// between differene Pair_maps.

	phc_TODO ();
	// Each alias_name can be converted in either the prefix or the suffix.
	// By_source and by_target need to be updated.

	// Symtables definitely need to be merged. Other storage nodes, I'm not
	// sure. So we'll merge them all.
	/*

	// Save the old alias pairs
	Map<Alias_name, int> old_abstract_counts = this->abstract_counts;
	Set<Alias_name> old_symtables = this->symtables;
	Set<Alias_pair*> old_all_pairs = this->all_pairs;

	// Clear the current set
	this->abstract_counts.clear ();
	this->symtables.clear ();
	this->all_pairs.clear ();
	this->by_source.clear ();
	this->by_target.clear ();


	foreach (Alias_pair* pair, old_all_pairs)
	{
		PT_node* source = pair->source->convert_context_name ();
		PT_node* target = pair->target->convert_context_name ();

		add_edge (source, target, pair->cert);
	}

	foreach (Alias_name name, old_symtables)
	{
		this->symtables.insert (name.convert_context_name ());
	}

	// I'm not really sure what to do here.
	Alias_name name;
	int count;
	foreach (tie (name, count), old_abstract_counts)
	{
		abstract_counts[name.convert_context_name ()] += count;
	}
	*/
}


	
/*
 * Nodes
 */
Storage_node* SN (string scope)
{
	return new Storage_node (scope);
}

Index_node* IN (string scope, string name)
{
	return new Index_node (scope, name);
}

Index_node* VN (string scope, MIR::VARIABLE_NAME* var)
{
	return IN (scope, *var->value);
}

Index_node* FN (string scope, MIR::FIELD_NAME* field)
{
	return IN (scope, *field->value);
}

Value_node*
ABSVAL (Index_node* node)
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
	assert (index != "");
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
	return Alias_name (storage, ABV);
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


Storage_node*
Index_node::get_owner ()
{
	return SN (this->storage);
}
