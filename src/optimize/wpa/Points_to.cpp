/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Points-to graph.
 *
 * There should be multiple graphs, 1 per function. there need to be links
 * between them, so I'm not clear if its better to have multiple regions within
 * a graph, or multiple graphs.
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

/*
 * High-level API
 */

void
Points_to::set_reference (MIR::VARIABLE_NAME* source, MIR::VARIABLE_NAME* target)
{
	// Remove whatever SOURCE uses to point to, and make it point to TARGET's ZVP
	Loc_node* sn = get_loc_node (source);
	Loc_node* tn = get_loc_node (target);

	Zval_node* zn;

	// If there's an existing source, we free it from its zvp.
	if (sn)
	{
		phc_TODO ();
	}
	else
		sn = add_node (new Loc_node (this, source));

	// If there's an existing target, we use it.
	if (!tn)
	{
		set_value (target, new MIR::NIL);
		tn = get_loc_node (target);
	}

	assert (tn);
	Zval_node_list* zns = tn->get_pointees <Zval_node> ();
	if (zns->size () != 1)
		phc_TODO ();
	zn = zns->front ();

	add_edge (sn, zn);
}


void
Points_to::set_value (MIR::VARIABLE_NAME* source, MIR::VARIABLE_NAME* target)
{
	// Set SOURCE's value to a copy of TARGET's value.
	
	// Get the source's zval.
	Loc_node* sn = get_loc_node (source);
	
	if (sn == NULL)
		phc_TODO ();

	Zval_node_list* zns = sn->get_pointees <Zval_node> ();
	if (zns->size () != 1)
		phc_TODO ();

	Zval_node* zn = zns->front ();


	// Get the target's value
	Loc_node* tn = get_loc_node (target);
	if (!tn)
		phc_TODO ();
	
	Value_node_list* vns = tn->get_pointees <Value_node> ();
	if (vns->size () != 1)
		phc_TODO ();

	Value_node* vn = vns->front ();

	Value_node* clone = add_node (vn->clone ());
	zn->remove_outgoing_edges ();
	add_edge (zn, clone);
}


void
Points_to::set_value (MIR::VARIABLE_NAME* source, MIR::Literal* target)
{
	Loc_node* ln = get_loc_node (source);

	if (ln)
	{
		// Change its value node: handles ref- and non-ref-sources
		phc_TODO ();
	}
	else
	{
		// Not in the graph: add: LOC -> ZVP -> VALUE
		Value_node* vn	= add_node (new Value_node (this, target));
		Zval_node* zn	= add_node (new Zval_node (this));
		ln					= add_node (new Loc_node (this, source));

		add_edge (ln, zn);
		add_edge (zn, vn);
	}
}


/*
 * Low-level API
 */

Loc_node*
Points_to::get_loc_node (MIR::VARIABLE_NAME* in)
{
	// Lookup existing node
	if (var_map.has (in))
		return var_map[in];

	return NULL;
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
	<< "graph [outputorder=edgesfirst];\n"
	<< "graph [labelloc=t];\n"
	<< "graph [label=\"" << *label << "\"];\n"
	;

	// Nodes
	foreach (vertex_pt v, vertices(bs))
	{
		PT_node* node = vn[v];
		cout << node->index << "[" << node->graphviz_attrs() << "];\n";
	}

	// Edges
	foreach (edge_pt e, edges (bs))
	{
		PT_edge* edge = ee[e];
		cout 
		<< edge->get_source ()->index << " -> " 
		<< edge->get_target ()->index << "[];\n";
	}

	cout
	<< "}\n"
	;
}



/*
 * Nodes
 */

PT_node::PT_node (Points_to* ptg)
: ptg (ptg)
{
	index = index_counter++;
}


Loc_node::Loc_node (Points_to* ptg, MIR::VARIABLE_NAME* var_name)
: PT_node (ptg)
, var_name (var_name)
{
}

string
Loc_node::graphviz_attrs ()
{
	stringstream ss;
	ss << "shape=ellipse,label=\"" << index << ": $" << *var_name->value << "\"";
	return ss.str ();
}

void
Loc_node::add_node_hook ()
{
	// We need to be able to look up nodes.
	assert (!ptg->var_map.has (var_name));
	ptg->var_map[var_name] = this;
}



Zval_node::Zval_node (Points_to* ptg)
: PT_node (ptg)
{
}

string
Zval_node::graphviz_attrs ()
{
	stringstream ss;
	ss << "shape=egg,label=\"" << index << ": ZVAL\"";
	return ss.str ();
}


Value_node::Value_node (Points_to* ptg, MIR::Literal* lit)
: PT_node (ptg)
, lit (lit)
{
}

string
Value_node::graphviz_attrs ()
{
	stringstream ss1;
	MIR_unparser mup (ss1, true);
	mup.unparse (lit);

	stringstream ss;
	ss 
	<< "shape=box,label=\"" << index << ": "
	<< demangle (lit, false) << ": " 
	<< *escape_DOT (s(ss1.str ()), 20) << "\"";
	return ss.str ();
}

Value_node*
Value_node::clone ()
{
	// TODO: i suspect we dont even need to clone the literal.
	return new Value_node (ptg, lit->clone ());
}

