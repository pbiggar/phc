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
	symtables["_SESSION"]++;
}

/*
 * Add a storage node for the scope (or it might exist already in the case of
 * recursion).
 */
void
Points_to::open_scope (string scope_name)
{
	symtables[scope_name]++;
}

void
Points_to::close_scope (string scope_name)
{
	symtables[scope_name]--;
	if (symtables[scope_name] == 0)
		symtables.erase(scope_name);

	// Remove the symbol table. Then do a mark-and-sweep from all the other
	// symbol tables.
	remove_node (SN (scope_name));
}

bool
Points_to::equals (Points_to* other)
{
	return this->by_source.equals (&other->by_source)
		&& this->by_target.equals (&other->by_target);
}


void
Points_to::dump_graphviz (String* label, Basic_block* bb, Whole_program* wp)
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

		stringstream ss;

		if (isa<Value_node> (node))
		{
			Abstract_value* val = wp->get_bb_out_abstract_value (bb, node->name());

			if (val->lit == BOTTOM)
				ss << "(B)";
			else if (val->lit == TOP)
				ss << "(T)";
			else
				dump_cell(val->lit, ss);

			ss << ", ";
		}

		if (isa<Storage_node> (node))
		{
			Abstract_value* val = wp->get_bb_out_abstract_value (bb, node->name());
			if (val->type == BOTTOM)
				ss << "(B)";
			else if (val->type == TOP)
				ss << "(T)";
			else
				dump_cell(val->type, ss);
		}


		cout
		<< *node->get_graphviz (ss.str ())
		<< "];\n" ;
	}

	// Add edges
	Alias_name source;
	Map<Alias_name, Alias_pair*> alias_map;
	foreach (tie (source, alias_map), by_source)
	{
		Alias_name target;
		Alias_pair* alias_pair;
		foreach (tie (target, alias_pair), alias_map)
		{
			cout 
			<< "\""
			<< *escape_DOT (s (source.str())) 
			<< "\" -> \"" 
			<< *escape_DOT (s (target.str())) 
			<< "\" [label=\""
			<< (alias_pair->cert == POSSIBLE ? "P" : "D")
			<< "\"];\n"
			;
		}

	}

	cout
	<< "}\n"
	;
}




void
Points_to::add_index (Index_node* index, certainty cert)
{
	Storage_node* st = index->get_storage();

	if (!has_node (index))
		add_edge (st, index, cert);
	else
	{
		// Dont update in place!!
		if (cert == DEFINITE)
			set_pair_cert (get_edge (st, index), DEFINITE);
	}
}

// Return a list of aliases which are references
Index_node_list*
Points_to::get_references (Index_node* index, certainty cert)
{
	return get_targets <Index_node> (index, cert);
}

// Get a list of aliases which are points-to.
Storage_node_list*
Points_to::get_values (Index_node* node)
{
	return get_targets <Storage_node> (node, PTG_ALL);
}

Index_node_list*
Points_to::get_indices (Storage_node* storage)
{
	return get_targets <Index_node> (storage, PTG_ALL);
}

Storage_node_list*
Points_to::get_storage_nodes ()
{
	Storage_node_list* result = new Storage_node_list;

	foreach (Alias_pair* pair, all_pairs)
	{
		if (isa<Storage_node> (pair->source))
			result->push_back (dyc<Storage_node> (pair->source));
	}

	return result;
}


void
Points_to::consistency_check (Basic_block* bb, Whole_program* wp)
{
	foreach (PT_node* node, *get_nodes ())
	{
		if (Index_node* ind = dynamic_cast<Index_node*> (node))
		{
			// Check index nodes are pointed to by their storage node
			Storage_node* st = ind->get_storage ();
			Alias_pair* incoming = get_edge (st, ind);
			if (incoming == NULL)
			{
				dump_graphviz (NULL, bb, wp);
				phc_internal_error ("No edge from storage node for %s",
										  ind->name().str().c_str());
			}

			// If there is only one outgoing edges from an index, then it must be
			// DEFINITE. If not, I'm not being careful with propagating CERTS.
			Storage_node_list* values = get_values (ind);
			if (values->size () == 1
				 && get_edge (ind, values->front())->cert != DEFINITE)
			{
				dump_graphviz (NULL, bb, wp);
				phc_internal_error ("Solo edge from %s to %s is not DEFINITE",
										  ind->name().str().c_str(),
										  values->front()->name().str().c_str());
			}

			// Check there isnt > 1 DEFINITE values
			if (values->size () > 1)
			{
				foreach (Storage_node* st, *values)
				{
					if (get_edge (ind, st)->cert == DEFINITE)
					{
						dump_graphviz (NULL, bb, wp);
						phc_internal_error (
								"Multiple edges from %s, but edge to %s is DEFINITE",
								ind->name().str().c_str(),
								st->name().str().c_str());
					}
				}
			}

			// We're disallowing POSSIBLE edges from a storage_node to an
			// index_node.
			if (incoming->cert == POSSIBLE)
			{
				dump_graphviz (NULL, bb, wp);
				phc_internal_error (
						"Edge from %s to %s is POSSIBLE",
						st->name().str().c_str(),
						ind->name().str().c_str());
			}
		}
		else
		{
			// TODO: storage node -> storage node edges arent allowed
		}
	}
}


// Mark all symtable nodes, then sweep anything they can reach. Remove the
// rest.
void
Points_to::remove_unreachable_nodes ()
{
	// XXX: The problem is that this leaves reference nodes behind. But we
	// only really want to remove the reference nodes that are out of scope.
	// So a node representing a variable should be removed when its symtable
	// does. What about other reference nodes? If there is an array with no
	// references to it, do we want to keep its index_nodes? Well, only if
	// they're references elsewhere. But if they're referenced elsewhere, the
	// useful info is already copied.

	// Summary: when removing a storage, remove all its index nodes.
	
	// Which means that until arrays and objects are modelled, this function
	// does nothing.
	return;

	// Put all symtables into the worklist
	PT_node_list* worklist = new PT_node_list;
	PT_node_list* all_nodes = get_nodes ();
	foreach (PT_node* node, *all_nodes)
	{
		// TODO: split between symtable and other storage nodes
		if (Storage_node* sn = dynamic_cast<Storage_node*> (node))
			worklist->push_back (sn);
	}

	// Mark all reachable nodes (use names, not pointers, as there may be
	// mulitple descirptor with the same name, but obviously different
	// pointers).
	Set<Alias_name> reachable;

	while (worklist->size () > 0)
	{
		PT_node* node = worklist->front ();
		worklist->pop_front ();

		if (reachable.has (node->name ()))
			continue;

		// mark reachable
		reachable.insert (node->name ());
	
		// Add successors to the worklist
		foreach (PT_node* succ, *get_targets<PT_node> (node))
		{
			worklist->push_back (succ);
		}
	}

	// remove all nodes not marked as reachable
	foreach (PT_node* node, *all_nodes)
	{
		// We use get_all_nodes because the vertex descriptors are invalidated
		// by remove_vertex
		if (!reachable.has (node->name ()))
		{
			phc_TODO ();
		}
	}
}


/*
 * Low-level API
 */

// Add the edge to the graph.
void
Points_to::add_edge (PT_node* n1, PT_node* n2, certainty cert)
{
	insert (new Alias_pair (n1, n2, cert));
}

// Add 2 edges, to and from N1 and N2.
void
Points_to::add_bidir_edge (PT_node* n1, PT_node* n2, certainty cert)
{
	insert (new Alias_pair (n1, n2, cert));
	insert (new Alias_pair (n2, n1, cert));
}

Points_to*
Points_to::clone ()
{
	Points_to* result = new Points_to;

	foreach (Alias_pair* p, this->all_pairs)
	{
		// No need to deep copy, as pairs are never updated in-place.
		result->insert (p);
	}

	return result;
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

	// Foreach storage node in G, check all other graphs for G. If they have
	// G, check for each I, such that G->I.
	foreach (Points_to* graph, *graphs)
	{
		foreach (Storage_node* stor, *graph->get_storage_nodes ())
		{
			foreach (Index_node* index, *graph->get_indices (stor))
			{
				// Check all the other graphs
				foreach (Points_to* other, *graphs)
				{
					if (graph == other)
						continue;

					if (other->has_node (stor) && !other->has_node (index))
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
	Points_to* result = new Points_to;

	// All edges from THIS.
	foreach (Alias_pair* p, this->all_pairs)
	{
		Alias_pair* other_pair = other->get_edge (p->source, p->target);
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
	return result;
}

PT_node_list*
Points_to::get_nodes ()
{
	// Only have the nodes once
	Map<Alias_name, PT_node*> all;

	foreach (Alias_pair* pair, all_pairs)
	{
		all[pair->source->name ()] = pair->source;
		all[pair->target->name ()] = pair->target;
	}

	return all.values();
}


void
Points_to::insert (Alias_pair* pair)
{
	Alias_name source = pair->source->name ();
	Alias_name target = pair->target->name ();

	// TODO: dont duplicate
	if (by_source[source].has (target))
	{
		// Dont update the edges in place
		Alias_pair* current = by_source[source][target];

		// Dont use combine cert.
		certainty cert = POSSIBLE;
		if (pair->cert == DEFINITE || current->cert == DEFINITE)
			cert = DEFINITE;

		set_pair_cert (current, cert);
	}
	else
	{
		by_source[source][target] = pair;
		by_target[target][source] = pair;

		// Record all pairs.
		all_pairs.insert (pair);
	}
}

bool
Points_to::has_node (PT_node* node)
{
	Alias_name name = node->name ();

	if (by_source[name].size ())
		return true;
	
	if (by_target[name].size ())
		return true;

	return false;
}

// And fail if its not present (unless !EXPECTED).
void
Points_to::remove_pair (PT_node* source, PT_node* target, bool expected)
{
	Alias_name s = source->name ();
	Alias_name t = target->name ();

	if (!by_source[s].has (t))
	{
		if (!expected)
			return;

		phc_unreachable ();
	}

	Alias_pair* edge = by_source[s][t];
	assert (edge);

	// Find the edge and remove it from all_pairs;
	all_pairs.erase (edge);

	// Remove it from by_source
	by_source[s].erase (t);

	// Remove it from by_target
	by_target[t].erase (s);


	// Check if the node can be removed
	maybe_remove_node (target);
}

void
Points_to::remove_pair (Alias_pair* pair, bool expected)
{
	// It might seem like a good idea to do have the other remove_pair call
	// this, but we want to use the Alias_pair* in the graph, whereas PAIR may
	// just be a descriptor.
	remove_pair (pair->source, pair->target, expected);
}


Alias_pair*
Points_to::get_edge (PT_node* source, PT_node* target)
{
	Alias_name s = source->name ();
	Alias_name t = target->name ();

	if (!by_source[s].has (t))
		return NULL;
	
	return by_source[s][t];
}

void
Points_to::set_pair_cert (Alias_pair* pair, certainty cert)
{
	if (pair->cert == cert)
		return;

	Alias_pair* new_pair = new Alias_pair (pair->source, pair->target, cert);
	remove_pair (pair);
	insert (new_pair);
}


void
Points_to::remove_node (PT_node* node)
{
	PT_node_list* children = get_targets<PT_node> (node);

	// dont use foreach, as remove_pair kills the iterators.
	while (by_source [node->name ()].size ())
	{
		Alias_name name;
		Alias_pair* pair;

		tie (name, pair) = *by_source [node->name ()].begin();
		remove_pair (pair->source, pair->target, true);
		remove_pair (pair->target, pair->source, false);
	}

	foreach (PT_node* child, *children)
	{
		maybe_remove_node (child);
	}
}

void
Points_to::maybe_remove_node (PT_node* node)
{
	// Remove index nodes with no storage node.
	if (isa<Index_node> (node))
	{
		if (!has_node (new Storage_node (dyc<Index_node> (node)->storage)))
			remove_node (node);
	}

	// Garbage collect. This is actually important, and not just for saving
	// space. Storage nodes may need to come back, typically if they are
	// implicitly created. We must make sure we get new results, as stale ones
	// may be wrong. Note this doesnt collect cycles, which is fine.
	if (isa<Storage_node> (node))
	{
		if ((get_incoming <PT_node> (node)->size() == 0)
				&& !is_symtable (dyc<Storage_node> (node)))
			remove_node (node);
	}
}

bool
Points_to::is_symtable (Storage_node* node)
{
	return symtables.has (node->storage);
}


/*
 * Alias-pairs
 */

Alias_pair::Alias_pair (PT_node* source, PT_node* target, certainty cert)
: source (source)
, target (target)
, cert (cert)
{
}

bool
Alias_pair::equals (Alias_pair* other)
{
	Alias_name this_source = this->source->name();
	Alias_name this_target = this->target->name();
	Alias_name other_source = other->source->name();
	Alias_name other_target = other->target->name();

	return this_source == other_source
			&& this_target == other_target
			&& this->cert == other->cert;
}

void
Alias_pair::dump()
{
	CHECK_DEBUG ();
	cdebug
	<< source->name ().str() << " -> "
	<< target->name ().str()
	<< " - " << cert;
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

Storage_node*
BB_array_node (Basic_block* bb)
{
	return new Storage_node (BB_array_name (bb));
}

Storage_node*
BB_object_node (Basic_block* bb)
{
	return new Storage_node (BB_object_name (bb));
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
Storage_node::get_graphviz (string info)
{
	stringstream ss;
	ss << "shape=box,label=\"" << storage << info << "\"";
	return s (ss.str ());
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
Index_node::get_graphviz (string info)
{
	stringstream ss;
	ss << "label=\"" << index << info << "\"";
	return s (ss.str ());
}

Storage_node*
Index_node::get_storage ()
{
	return new Storage_node (this->storage);
}

Value_node::Value_node (Index_node* owner)
: Storage_node(owner->name().str())
{
	assert (storage != "");
}

Alias_name
Value_node::name ()
{
	return Alias_name (storage, ABV);
}

String*
Value_node::get_graphviz (string info)
{
	stringstream ss;
	ss << "color=red,label=\"" << info << "\"";
	return s (ss.str ());
}
