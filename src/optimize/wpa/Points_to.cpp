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


class PT_node : virtual public GC_obj
{
public:
	int index;
	vertex_pt vertex;

	// Each allocated node gets a unique index
	static int index_counter;
	PT_node()
	{
		index = index_counter++;
	}

	virtual string graphviz_attrs () = 0;
};

int PT_node::index_counter = 0;

// TODO: different kinds of nodes for fields, variables, arrays, objects and
// atoms?
class Var_node : public PT_node
{
public:
	MIR::VARIABLE_NAME* var_name;
	Var_node (MIR::VARIABLE_NAME* var_name)
	: var_name (var_name)
	{
	}

	string graphviz_attrs ()
	{
		stringstream ss;
		ss << "label=\"" << *var_name->value << "\"";
		return ss.str ();
	}
};

class Atom_node : public PT_node
{
public:
	MIR::Node* atom; // constant or literal
	Atom_node (MIR::Node* atom)
	: atom (atom)
	{
		assert (isa<MIR::Literal> (atom) || isa<MIR::Constant> (atom));
	}

	string graphviz_attrs ()
	{
		stringstream ss;
		ss << "label=\"" << demangle (atom, false) << "\"";
		return ss.str ();
	}
};

class PT_edge : virtual public GC_obj
{
	Points_to* ptg;
	// TODO: do we want the edge to have types?
public:
	edge_pt edge;

	PT_edge (Points_to* ptg, edge_pt edge)
	: ptg (ptg)
	, edge (edge)
	{
	}

	PT_node* get_source ()
	{
		return ptg->vn[source (edge, ptg->bs)];
	}

	PT_node* get_target ()
	{
		return ptg->vn[target (edge, ptg->bs)];
	}
};


Points_to::Points_to()
{
	atom = new Atom_node (new MIR::STRING (s("TODO")));
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

	Var_node* node = new Var_node (var);
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


