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


int PT_node::index_counter = 0;


Points_to::Points_to()
{
}

#define ST_NAME "__PHC_ST__"
void
Points_to::setup_function (string ns)
{
	// The symtable and its zval
	Array_node* st = add_array_node (ns);
	Zval_node* zval = add_zval_node (ns);
	add_named_edge (new Location (st, ST_NAME), zval);
	add_edge (zval, st);

	assert (!symtables.has(ns));
	symtables[ns] = st;

	// TODO: add the superglobals (its wrong to add the parameters before the
	// superglobals, but we've only 1 example of this breaking).
	
	// Actually, we need GLOBALS anyway.
	if (ns == "__MAIN__")
	{
		// Dont use API, as this is a special case
		Zval_node* global = add_zval_node (ns);
		add_named_edge (new Location (st, "GLOBALS"), global);
		add_edge (global, st);
	}
	else
	{
		set_reference (
			get_var (ns, new MIR::VARIABLE_NAME ("GLOBALS")),
			get_var ("__MAIN__", new MIR::VARIABLE_NAME ("GLOBALS")));
	}
}

void
Points_to::clear_function (string ns)
{
	if (ns != "__MAIN__")
	{
		Storage_node* st = get_symtable (ns)->node;
		remove_node (st);
		remove_unreachable_nodes ();
	}
}

void
Points_to::set_reference (Location* sn, Location* tn)
{
	// Important: get this before killing sn
	Zval_node* rhs = get_zval_node (tn, true);

	// This is killing too.
	remove_named_edge (sn);

	add_named_edge (sn, rhs);
}
void
Points_to::copy_value (Location* loc1, Location* loc2)
{
	phc_TODO ();
/*	
	Zval_node_list* zns = loc1->get_pointees <Zval_node> ();
	if (zns->size () != 1)
		phc_TODO ();

	Zval_node* zn = zns->front ();



	Value_node_list* vns = loc2->get_pointees <Value_node> ();
	if (vns->size () != 1)
		phc_TODO ();

	Value_node* vn = vns->front ();

	Value_node* clone = add_node (vn->clone ());
	zn->remove_outgoing_edges ();
	add_edge (zn, clone);
	*/
}

/* TODO: It needs to be a lot clearer what happens when there are multiple
 * zvals, etc, for a single location. But that wont happen til
 * flow-sensitivity */
void
Points_to::set_value (Location* loc, Value_node* val)
{
	Zval_node* zn = get_zval_node (loc, true);

	// Strong update (aka kill)
	zn->remove_outgoing_edges ();

	add_edge (zn, val);
}




Array_node*
Points_to::add_array_node (string ns)
{
	return add_node (new Array_node (this, ns));
}

// TODO: Literals do not need namespaces. In fact, nothing does except the st
// entries.
Lit_node*
Points_to::add_lit_node (string ns, MIR::Literal* lit)
{
	return add_node (new Lit_node (this, ns, lit));
}

Zval_node*
Points_to::add_zval_node (string ns)
{
	return add_node (new Zval_node (this, ns));
}

Zval_node*
Points_to::get_zval_node (Location* loc, bool init)
{
	Zval_node* result = loc->get_zval_node ();
	if (result)
		return result;

	if (init)
	{
		result = add_zval_node (loc->node->ns);
		add_named_edge (loc, result);
		return result;
	}
	else
		// TODO: not sure this should be allowed
		phc_TODO ();
}

Lit_node*
Points_to::get_lit_node (Location* index)
{
	Zval_node* zn = index->get_zval_node ();
	return zn->get_only_target<Lit_node> ();
}

Location*
Points_to::get_var (string ns, MIR::VARIABLE_NAME* var)
{
	return get_location (get_symtable (ns), *var->value);
}


/*
 * Low-level API
 */

Location*
Points_to::get_location (Location* loc, string value)
{
	Zval_node* zn = loc->get_zval_node ();
	Storage_node* store = zn->get_only_target <Storage_node> ();
	return new Location (store, value);
}

Location*
Points_to::get_symtable (string ns)
{
	// Don't call anything else, as everything calls this
	return new Location (symtables[ns], ST_NAME);
}



PT_edge*
Points_to::add_edge (PT_node* source, PT_node* target)
{
	std::pair<edge_pt,bool> pair = boost::add_edge (source->vertex, target->vertex, bs);

	// The graph should allow parallel edges.
	assert (pair.second);

	edge_pt e = pair.first;
	ee[e] = new PT_edge (this, e);
	return ee[e];
}

Named_edge*
Points_to::add_named_edge (Location* loc, Zval_node* target)
{
	// TODO: abstract
	std::pair<edge_pt,bool> pair = boost::add_edge (loc->node->vertex, target->vertex, bs);

	// The graph should allow parallel edges.
	assert (pair.second);

	edge_pt e = pair.first;
	Named_edge* result = new Named_edge (loc->name, this, e);
	ee[e] = result;
	return result;
}

void
Points_to::remove_named_edge (Location* loc)
{
	loc->node->remove_named_edge (loc->name);
}

void
Points_to::remove_node (PT_node* node)
{
	boost::clear_vertex (node->vertex, bs);
	boost::remove_vertex (node->vertex, bs);
}

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

	// TODO: we can probably just get the list of functions from the callgraph later.

	// Nodes
	foreach (vertex_pt v, vertices(bs))
	{
		PT_node* node = vn[v];
		cout
		<< "subgraph cluster_" << node->ns << " { " 
		<< "graph [label=\"" << node->ns << "\"];\n" // TODO: this adds the label too often
		<< node->index << " [" << node->graphviz_attrs() << "]; }\n";
	}

	// Edges
	foreach (edge_pt e, edges (bs))
	{
		PT_edge* edge = ee[e];
		cout 
		<< edge->get_source ()->index << " -> " 
		<< edge->get_target ()->index 
		<< "[" << edge->graphviz_attrs () << "];\n";
	}

	cout
	<< "}\n"
	;
}


/*
 * Nodes
 */

PT_node::PT_node()
{
}

PT_node::PT_node (Points_to* ptg, string ns)
: ptg (ptg)
, ns (ns)
{
	index = index_counter++;
}



Zval_node::Zval_node (Points_to* ptg, string ns)
: PT_node (ptg, ns)
{
}

string
Zval_node::graphviz_attrs ()
{
	stringstream ss;
	ss << "shape=circle,fixedsize=true,height=0.4,label=\"" << index << "\"";
	return ss.str ();
}

Value_node::Value_node()
{
}

Lit_node::Lit_node (Points_to* ptg, string ns, MIR::Literal* lit)
: PT_node (ptg, ns)
, lit (lit)
{
}

string
Lit_node::graphviz_attrs ()
{
	stringstream ss;
	ss 
	<< "shape=box,label=\"" << index << ": "
	<< *escape_DOT (lit->get_value_as_string (), 20) << "\"";
	return ss.str ();
}

Value_node*
Lit_node::clone ()
{
	// TODO: i suspect we dont even need to clone the literal.
	return new Lit_node (ptg, ns, lit->clone ());
}

Zval_node*
Location::get_zval_node ()
{
	return node->get_indexed (name);
}


Zval_node*
Storage_node::get_indexed (string index)
{
	// TODO: this is crying out for a hashing (or at least a map)
	foreach (edge_pt out_edge, out_edges (vertex, ptg->bs))
	{
		Named_edge* edge = dyc<Named_edge> (ptg->ee[out_edge]);
		if (index == edge->name)
			return dyc<Zval_node> (edge->get_target ());
	}
	return NULL;
}

void
Storage_node::remove_named_edge (string name)
{
	// TODO: hashtable
	foreach (edge_pt out_edge, out_edges (vertex, ptg->bs))
	{
		Named_edge* edge = dyc<Named_edge> (ptg->ee[out_edge]);
		if (edge->name == name)
		{
			boost::remove_edge (out_edge, ptg->bs);
			break;
		}
	}
}

Array_node::Array_node (Points_to* ptg, string ns)
: PT_node (ptg, ns)
{
}

string
Array_node::graphviz_attrs ()
{
	stringstream ss;
	ss 
	<< "shape=box,label=\"" << index << ": Array\"";
	return ss.str ();
}

Value_node*
Array_node::clone ()
{
	phc_TODO ();
}
