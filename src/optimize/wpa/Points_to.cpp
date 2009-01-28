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

#include "Points_to.h"
#include "MIR.h"
#include "lib/error.h"
#include "lib/escape.h"
#include "lib/demangle.h"
#include "process_ir/General.h"

using namespace MIR;
using namespace std;
using namespace boost;

#define ST_NAME "__PHC_ST__"

Points_to::Points_to ()
{
	pairs = new Pairs;
}

Storage_node* SN (string scope) { return new Storage_node (scope); }
Index_node* IN (string scope, string name) { return new Index_node (scope, name); }
Index_node* VN (string scope, MIR::VARIABLE_NAME* var) { return IN (scope, *var->value); }
Index_node* FN (string scope, MIR::FIELD_NAME* field) { return IN (scope, *field->value); }


/*
 * Add a storage node for the scope (or it might exist already in the case of
 * recursion). Add an GLOBALS node to it.
 */
void
Points_to::open_scope (string scope_name)
{
	// TODO: add the superglobals (its wrong to add the parameters before the
	// superglobals, but we've only 1 example of this breaking).
	
	// Add the GLOBALS node

	if (scope_name == "__MAIN__")
	{
		add_edge (SN (scope_name), IN (scope_name, "GLOBALS"), DEFINITE);
		add_edge (IN (scope_name, "GLOBALS"), SN (scope_name));
	}
	else
	{
		// We need to remove the "global $GLOBALS;" statements, since they're wrong, but we should remove it here first.
//		set_reference (IN (scope_name, "GLOBALS"), IN ("__MAIN__", "GLOBALS"));
	}
}

void
Points_to::close_scope (string scope_name)
{
	phc_TODO ();
}

void
Points_to::dump_graphviz (String* label)
{
	if (label == NULL)
	{
		CHECK_DEBUG ();
		label = s("TEST");
	}

	cout
	<< "digraph G {\n"
	<< "graph [labelloc=t];\n"
	<< "graph [label=\"" << *label << "\"];\n"
	;

	// TODO: add nodes, with different shapes for different nodes.

	// Add definite edges
	string source;
	Map<string, Alias_pair*> alias_map;
	foreach (tie (source, alias_map), pairs->by_source)
	{
		string target;
		Alias_pair* alias_pair;
		foreach (tie (target, alias_pair), alias_map)
		{
			// Source
			cout
			<< "\""
			<< *escape_DOT (s (source))
			<< "\" [" << *alias_pair->source->get_graphviz ()
			<< "];\n"
			;
			
			// Target
			cout
			<< "\""
			<< *escape_DOT (s (target))
			<< "\" [" << *alias_pair->target->get_graphviz ()
			<< "];\n"
			;

			// Edge
			cout 
			<< "\""
			<< *escape_DOT (s(source)) 
			<< "\" -> \"" 
			<< *escape_DOT (s(target)) 
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

// Add the edge to the graph.
void
Points_to::add_edge (PT_node* n1, PT_node* n2, certainty cert)
{
	pairs->insert (new Alias_pair (n1, n2, cert));
}

// Add 2 edges, to and from N1 and N2.
void
Points_to::add_bidir_edge (PT_node* n1, PT_node* n2, certainty cert)
{
	pairs->insert (new Alias_pair (n1, n2, cert));
	pairs->insert (new Alias_pair (n2, n1, cert));
}

Points_to*
Points_to::clone ()
{
	Points_to* result = new Points_to;

	foreach (Alias_pair* p, this->pairs->all_pairs)
	{
		// No need to deep copy, as pairs are never updated in-place.
		result->pairs->insert (p);
	}

	return result;
}

void
Points_to::kill_value (Index_node* index)
{
	Storage_node_list* values = get_points_to (index, PTG_ALL);
	if (values->size ())
		phc_TODO (); // kill, and the things it points to - watch of for may-aliases
}

// Remove all references edges into or out of INDEX. Also call kill_value.
void
Points_to::kill_references (Index_node* index)
{
	foreach (Index_node* other, *get_references (index, PTG_ALL))
	{
		pairs->remove_pair (index, other);
		pairs->remove_pair (other, index);
	}
}


// Kill the value of INDEX (which indicates a scalar is being assigned
// here). This only updates the graph if an object or array is killed. If the
// node is not in the graph, add it.
void
Points_to::set_scalar_value (Index_node* index)
{
	if (contains (index))
		kill_value (index);

	add_node (index);
}

void
Points_to::add_node (Index_node* index)
{
	add_edge (SN (index->storage), index);
}

// Does the graph already contains this node.
bool
Points_to::contains (Index_node* index)
{
	// TODO: check its connected to a storage node
	return pairs->has_node (index);
}

// Make N1 alias N2. Kills N1. Initialized N2 if it is not already.
void
Points_to::set_reference (Index_node* n1, Index_node* n2)
{
	if (!contains (n2))
	{
		add_node (n2);
		phc_TODO (); // initialize to NULL
	}

	if (!contains (n1))
		add_node (n1);
	else
		kill_references (n1);

	// TODO: abstract

	// Copy all edges to reference nodes
	certainty certainties[] = {POSSIBLE, DEFINITE};
	foreach (certainty cert, certainties)
	{
		Index_node_list* refs = get_references (n2, cert);
		foreach (Index_node* ref, *refs)
			add_bidir_edge (n1, ref);
	}


	// Copy all edges to storage nodes
	foreach (certainty cert, certainties)
	{
		Storage_node_list* pts = get_points_to (n2, cert);
		foreach (Storage_node* st, *pts)
			add_edge (n1, st);
	}

	add_bidir_edge (n1, n2);
}

// Copy the current value from N2 to N1. This clones N2's array, points N1
// and N2 to the same object for object's, and kills existing values for N1.
void
Points_to::copy_value (Index_node* n1, Index_node* n2)
{
	if (!contains (n1) || !contains (n2))
		phc_TODO ();

	// This kills the value of N1, and may lead to a clone on N2's value.
	if (has_value_edges (n1) || has_value_edges (n2))
		phc_TODO ();
}

// Does the node have edges pointing to a storage node
bool
Points_to::has_value_edges (Index_node* source)
{
	return get_points_to (source, PTG_ALL)->size () != 0;
}

// Return a list of aliases which are references
Index_node_list*
Points_to::get_references (Index_node* index, certainty cert)
{
	return get_aliases <Index_node> (index, cert);
}

// Only get the aliasias which are indices or Storage node NS
Index_node_list*
Points_to::get_local_references (Storage_node* sn, Index_node* node, certainty cert)
{
	Index_node_list* tmp = get_aliases <Index_node> (node, cert);

	// Its very awkward to do this in-place.
	Index_node_list* result = new Index_node_list;
	foreach (Index_node* node, *tmp)
	{
		if (sn->name == node->storage)
			result->push_back (node);
	}

	return result;
}

// Get a list of aliases which are points-to.
Storage_node_list*
Points_to::get_points_to (Index_node* node, certainty cert)
{
	return get_aliases <Storage_node> (node, cert);
}


/*
 * Alias-pair representation
 */


Pairs::Pairs ()
{
}

void
Pairs::insert (Alias_pair* pair)
{
	string source = pair->source->get_unique_name ();
	string target = pair->target->get_unique_name ();

	// TODO: dont duplicate
	if (by_source[source].has (target))
		phc_TODO ();

	if (by_target[target].has (source))
		phc_TODO ();

	by_source[source][target] = pair;
	by_target[target][source] = pair;

	// Record all pairs.
	all_pairs.insert (pair);
}

bool
Pairs::has_node (PT_node* node)
{
	// TODO: make this lookup faster
	string name = node->get_unique_name ();

	if (by_source[name].size ())
		return true;
	
	if (by_target[name].size ())
		return true;

	return false;
}

void
Pairs::remove_pair (PT_node* source, PT_node* target)
{
	string s = source->get_unique_name ();
	string t = target->get_unique_name ();

	Alias_pair* edge = by_source[s][t];
	assert (edge);

	// Find the edge and remove it from all_pairs;
	all_pairs.erase (edge);

	// Remove it from by_source
	by_source[s].erase (t);

	// Remove it from by_target
	by_target[t].erase (s);
}

Alias_pair::Alias_pair (PT_node* source, PT_node* target, certainty cert)
: source (source)
, target (target)
, cert (cert)
{
}

void
Alias_pair::dump()
{
	CHECK_DEBUG ();
	cdebug
	<< source->get_unique_name () << " -> "
	<< target->get_unique_name ()
	<< " - " << cert;
}


/*
 * Nodes
 */

Storage_node::Storage_node (string name)
: name (name)
, is_abstract (false)
{
}

string
Storage_node::get_unique_name ()
{
	stringstream ss;
	ss << "ST:" << name;
	return ss.str ();
}

String*
Storage_node::get_graphviz ()
{
	stringstream ss;
	ss << "shape=box";
	return s (ss.str ());
}

Index_node::Index_node (string storage, string name)
: storage (storage)
, name (name)
{
}

string 
Index_node::get_unique_name ()
{
	stringstream ss;
	ss << storage << "::" << name;
	return ss.str ();
}

String*
Index_node::get_graphviz ()
{
	return s("");
}





#if 0

// The old points-to. Only 1 bit of code we'd like to re-use remains.
void
Points_to::remove_unreachable_nodes ()
{
	Set<PT_node*> reachable;

	// Mark-sweep to remove unreachable nodes.
	PT_node_list* worklist = new PT_node_list (symtables["__MAIN__"]);

	while (worklist->size () > 0)
	{
		PT_node* node = worklist->front ();
		worklist->pop_front ();

		// Dont process BBs we've seen before
		if (reachable.has (node))
			continue;

		// mark reachable
		reachable.insert (node);
	
		// Add successors to the worklist
		foreach (PT_node* succ, *node->get_targets<PT_node> ())
			worklist->push_back (succ);
	}

	// remove all nodes not marked as reachable
	foreach (PT_node* node, *get_nodes<PT_node> ())
	{
		// We use get_all_nodes because the vertex descriptors are invalidated
		// by remove_vertex
		if (!reachable.has (node))
		{
			boost::clear_vertex (node->vertex, bs);
			boost::remove_vertex (node->vertex, bs);
		}
	}
}


#endif
