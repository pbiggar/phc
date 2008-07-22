/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Control-flow Graph
 */

#include "CFG.h"
#include "process_ir/General.h"
#include "boost/graph/graphviz.hpp"
#include "process_ast/DOT_unparser.h"
#include "boost/foreach.hpp"

using namespace boost;
using namespace std;
using namespace MIR;

CFG::CFG ()
: bs()
{
	bb = get(vertex_bb_t(), bs);
}

void
CFG::add_statements (List<Statement*>* statements)
{
	vertex_t entry = add_vertex (bs);
	bb[entry] = new Entry_block;

	// Keep track of labels, for edges between gotos and branches.
	map <string, vertex_t> labels;

	// In the second pass, we'll need the vertices to add edges.
	map <Statement*, vertex_t> nodes;


	// In the first pass, just create nodes for the statements.
	for_lci (statements, Statement, i)
	{
		vertex_t v = add_vertex (bs);;
		nodes[*i] = v;

		if (isa<Label> (*i))
			labels [*dyc<Label>(*i)->label_name->get_value_as_string ()] = v;
	}


	// Create the edges
	vertex_t parent = entry;
	bool use_parent = true; // parent is just an int, so not nullable

	for_lci (statements, Statement, i)
	{
		// Be careful with pointers. Its very easy to overwrite vertices
		vertex_t v = nodes[*i];
		if (use_parent)
		{
			add_edge (parent, v, bs);
		}
		switch ((*i)->classid())
		{
			case Label::ID:
				bb[v] = new Empty_block;
				parent = v;
				use_parent = true;
				break;

			case Goto::ID:
			{
				bb[v] = new Empty_block;
				use_parent = false;
				vertex_t target = 
					labels[*dyc<Goto>(*i)->label_name->get_value_as_string ()];
				add_edge (v, target, bs);
				break;
			}

			case Branch::ID:
			{
				Branch* b = dyc<Branch>(*i);
				bb[v] = new Branch_block (b);
				vertex_t iftrue = labels[*b->iftrue->get_value_as_string ()];
				vertex_t iffalse = labels[*b->iffalse->get_value_as_string ()];
				add_edge (v, iftrue, bs);
				add_edge (v, iffalse, bs);
				break;
			}

			default:
				bb[v] = new Statement_block (*i);
				use_parent = true;
				parent = v;
				break;
		}
	}
	
	vertex_t exit = add_vertex (bs);
	bb[exit] = new Exit_block;

	assert (use_parent);
	add_edge (parent, exit, bs);


	// Check that no blocks have NULL vertices
	BOOST_FOREACH (vertex_t v, vertices (bs))
	{
		assert (bb[v] != NULL);
	}

}

// Dump to graphviz
struct BB_property_functor
{
	property_map<Graph, vertex_bb_t>::type bb;
	BB_property_functor (CFG* cfg)
	{
		bb = cfg->bb;
	}
	void operator()(std::ostream& out, const edge_t& v) const 
	{
		// No edges properties
		// TODO add true and false for Branches
	}

	void operator()(std::ostream& out, const vertex_t& v) const 
	{
		out << " [label=\"" << *DOT_unparser::escape (bb[v]->get_graphviz_label ()) << "\"";
		String* prop = bb[v]->get_graphviz_properties ();
		if (prop)
			out << ", " << *prop << " ";
		
		out << "]";
	}
};

struct Graph_property_functor
{
	void operator()(std::ostream& out) const 
	{
		out << "graph [outputorder=edgesfirst]" << std::endl;
	}
};

void
CFG::dump_graphviz ()
{
	write_graphviz (
		cout, 
		bs, 
		BB_property_functor(this),
		BB_property_functor(this),
		Graph_property_functor());
}
