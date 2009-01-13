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
#include "lib/demangle.h"
#include "process_ir/General.h"

using namespace MIR;
using namespace std;
using namespace boost;


int PT_node::index_counter = 0;


Points_to::Points_to()
{
	atom = new Atom_node (this, new MIR::STRING (s("TODO")));
	add_node (atom);
}

PT_node*
Points_to::get_node (MIR::Expr* in)
{
	// There are only a few types allowed here: Literals, Constants and VARIABLE_NAMEs.
	if (Constant* constant = dynamic_cast<Constant*> (in))
		phc_TODO ();

	if (Literal* lit = dynamic_cast<Literal*> (in))
		return atom;

	VARIABLE_NAME* var = dyc<VARIABLE_NAME> (in);

	// Lookup existing node
	if (node_map.has (var))
		return node_map[var];

	Var_node* node = new Var_node (this, var);
	add_node (node);
	node_map[var] = node;

	return node;
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
Points_to::add_node (PT_node* node)
{
	assert (node->vertex == NULL);
	vertex_pt v = add_vertex (bs);
	vn[v] = node;
	node->vertex = v;
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

PT_node::PT_node (Points_to* prg)
: ptg (ptg)
{
	index = index_counter++;
}


Var_node::Var_node (Points_to* ptg, MIR::VARIABLE_NAME* var_name)
: PT_node (ptg)
, var_name (var_name)
{
}

string
Var_node::graphviz_attrs ()
{
	stringstream ss;
	ss << "label=\"" << index << ": " << *var_name->value << "\"";
	return ss.str ();
}

Atom_node::Atom_node (Points_to* ptg, MIR::Node* atom)
: PT_node (ptg)
, atom (atom)
{
	assert (isa<MIR::Literal> (atom) || isa<MIR::Constant> (atom));
}

string
Atom_node::graphviz_attrs ()
{
	stringstream ss;
	ss << "label=\"" << index << ": " << demangle (atom, false) << "\"";
	return ss.str ();
}



