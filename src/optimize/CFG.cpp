/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Control-flow Graph
 */

#include "boost/foreach.hpp"
#include "boost/graph/graphviz.hpp"
#include "boost/graph/depth_first_search.hpp"
#include "boost/graph/visitors.hpp"

#include "CFG.h"
#include "process_ast/DOT_unparser.h"
#include "process_ir/General.h"

using namespace boost;
using namespace std;
using namespace MIR;

CFG::CFG ()
: bs()
, next_id (0)
{
	vb = get(vertex_bb_t(), bs);
	index = get(vertex_index_t(), bs);

	// Initialize the entry and exit blocks
	entry = add_bb (new Entry_block);
	exit = add_bb (new Exit_block);
}

vertex_t
CFG::add_bb (Basic_block* bb)
{
	vertex_t v = add_vertex (bs);
	vb[v] = bb;
	bb->vertex = v;

	// IDs are used by graphviz
	index[v] = next_id++;

	return v;
}

void
CFG::add_statements (List<Statement*>* statements)
{
	// Keep track of labels, for edges between gotos and branches.
	map <string, vertex_t> labels;

	// In the second pass, we'll need the vertices to add edges.
	map <Statement*, vertex_t> nodes;


	// In the first pass, just create nodes for the statements.
	for_lci (statements, Statement, i)
	{
		vertex_t v;
		switch ((*i)->classid())
		{
			case Label::ID:
				v = add_bb (new Empty_block);
				labels [*dyc<Label>(*i)->label_name->get_value_as_string ()] = v;
				break;

			case Goto::ID:
				v = add_bb (new Empty_block);
				break;

			case Branch::ID:
				v = add_bb (new Branch_block (dyc<Branch>(*i)));
					break;

			default:
				v = add_bb (new Statement_block (*i));
				break;
		}
		nodes[*i] = v;
	}


	// Create the edges
	vertex_t parent = entry;
	bool use_parent = true; // parent is just an int, so not nullable

	foreach (Statement* s, *statements)
	{
		// Be careful with pointers. Its very easy to overwrite vertices
		vertex_t v = nodes[s];
		if (use_parent)
			add_edge (parent, v, bs);


		switch (s->classid())
		{
			case Goto::ID:
			{
				vertex_t target = 
					labels[*dyc<Goto>(s)->label_name->get_value_as_string ()];
				add_edge (v, target, bs);

				use_parent = false;
				break;
			}

			case Branch::ID:
			{
				Branch* b = dyc<Branch>(s);
				vertex_t iftrue = labels[*b->iftrue->get_value_as_string ()];
				vertex_t iffalse = labels[*b->iffalse->get_value_as_string ()];
				add_edge (v, iftrue, bs);
				add_edge (v, iffalse, bs);

				use_parent = false;
				break;
			}

			default:
				parent = v;
				use_parent = true;
				break;
		}
	}
	
	assert (use_parent);
	add_edge (parent, exit, bs);

	consistency_check ();
}

Basic_block*
CFG::get_entry_bb ()
{
	return vb[entry];
}

Basic_block*
CFG::get_exit_bb ()
{
	return vb[exit];
}

list<Basic_block*>*
CFG::get_predecessors (Basic_block* bb)
{
	list<Basic_block*>* result = new list<Basic_block*>;

	foreach (edge_t e, in_edges (bb->vertex, bs))
	{
		result->push_back (vb[source (e, bs)]);
	}

	return result;
}

list<Basic_block*>*
CFG::get_successors (Basic_block* bb)
{
	list<Basic_block*>* result = new list<Basic_block*>;

	foreach (edge_t e, out_edges (bb->vertex, bs))
	{
		result->push_back (vb[target (e, bs)]);
	}

	return result;
}

list<Basic_block*>*
CFG::get_all_bbs ()
{

	list<Basic_block*>* result = new list<Basic_block*>;

	foreach (vertex_t v, vertices(bs))
	{
		result->push_back (vb[v]);
	}

	return result;
}

// Dump to graphviz
struct BB_property_functor
{
	property_map<Graph, vertex_bb_t>::type vb;
	BB_property_functor (CFG* cfg)
	{
		vb = cfg->vb;
	}
	void operator()(std::ostream& out, const edge_t& v) const 
	{
		// TODO add true and false for Branches

		// Head and tail annotatations are done in the vertex, because the
		// headlabel and taillabel attributes dont expand the area they are
		// in, and so are frequently unreadable.
	}

	void operator()(std::ostream& out, const vertex_t& v) const 
	{
		out << "[label=\"";

		// IN annotations
		pair<String*, Set*> props;
		stringstream ss1;
		foreach (props, *vb[v]->get_graphviz_head_properties ())
		{
			if (props.second->bs.size ())
			{
				ss1 << *props.first << " = [";
				foreach (string str, props.second->bs)
				{
					ss1 << str << ", ";
				}
				ss1 << "]\\n";
			}
		}

		// BB source
		stringstream ss2;
		ss2 << *DOT_unparser::escape (vb[v]->get_graphviz_label ());

		// BB properties
		stringstream ss3;
		foreach (props, *vb[v]->get_graphviz_bb_properties ())
		{
			if (props.second->bs.size ())
			{
				ss3 << *props.first << " = [";
				foreach (string str, props.second->bs)
				{
					ss3 << str << ", ";
				}
				ss3 << "]\\n";
			}
		}

		// OUT annotations
		stringstream ss4;
		foreach (props, *vb[v]->get_graphviz_tail_properties ())
		{
			if (props.second->bs.size ())
			{
				ss4 << *props.first << " = [";
				foreach (string str, props.second->bs)
				{
					ss4 << str << ", ";
				}
				ss4 << "]\\n";
			}
		}

		// Print out all 4 stringstreams, with line-break;
		out << ss1.str();
		if (ss1.str().size())
			out << "\\n"; // blank line before source
		out << ss2.str();
		if (ss3.str().size() || ss4.str().size())
			out << "\\n\\n"; // blank line after source
		out << ss3.str();
		out << ss4.str();
		if (ss3.str().size() || ss4.str().size())
			out << "\b\b";

		
		out << "\"]";
	}
};

struct Graph_property_functor
{
	String* label;
	Graph_property_functor(String* label) : label (label) {}
	void operator()(std::ostream& out) const 
	{
		out << "graph [outputorder=edgesfirst];" << std::endl;
		out << "graph [label=\"" << *label << "\"];" << std::endl;
	}
};

void
CFG::dump_graphviz (String* label)
{
	consistency_check ();
	write_graphviz (
		cout, 
		bs, 
		BB_property_functor(this),
		BB_property_functor(this),
		Graph_property_functor(label));
}

/* Error checking */
void
CFG::consistency_check ()
{
	// The graph should never reuse vertices.
	foreach (vertex_t v, vertices (bs))
	{
		assert (vb[v]->vertex == v);
	}
}

void
CFG::remove_bb (Basic_block* bb)
{
	vertex_t v = bb->vertex;

	clear_vertex (v, bs);
	remove_vertex (v, bs);
}

void
CFG::replace_bb (Basic_block* bb, list<Basic_block*>* replacements)
{
	if (replacements->size() == 1
		&& replacements->front() == bb)
	{
		// Same BB: do nothing
	}
	else if (replacements->size() == 0)
	{
		// Remove the BB
		foreach (Basic_block* pred, *get_predecessors (bb))
			foreach (Basic_block* succ, *get_successors (bb))
				add_edge (pred->vertex, succ->vertex, bs);

		remove_bb (bb);
	}
	else
	{
		foreach (Basic_block* new_bb,* replacements)
		{
			// Create vertices for the new statements
			vertex_t v = add_bb (new_bb);

			// Add edges from predecessors
			foreach (Basic_block* pred, *get_predecessors (bb))
				add_edge (pred->vertex, v, bs);

			// Add edges from asuccessors 
			foreach (Basic_block* succ, *get_successors (bb))
				add_edge (v, succ->vertex, bs);
		}
		remove_bb (bb);
	}
}

// Do a depth first search. For each block, add a label, and a goto to the next
// block(s).
class Linearizer : public default_dfs_visitor
{
public:
	List<Statement*>* statements;
	map<vertex_t, LABEL_NAME*> labels;
	Linearizer()
	{
		statements = new List<Statement*>;
	}

	/* Assign a label for each block. */
	void initialize_vertex (vertex_t v, const Graph& g)
	{
		labels [v] = fresh_label_name ();
	}

	/* Return a Goto to the next statement. */
	Goto* get_goto_next (Basic_block* bb, const Graph& g)
	{
		vertex_t v = bb->vertex;
		assert (out_degree (v, g) == 1);
		vertex_t t = target (*out_edges (v, g).first, g);
		return new Goto (labels[t]);
	}

	void discover_vertex (vertex_t v, const Graph& g)
	{
		Basic_block* bb = get(vertex_bb_t(), g)[v];

		if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
		{
			statements->push_back (new Label(labels[v]->clone ()));
			statements->push_back (sb->statement);
			statements->push_back (get_goto_next (bb, g));
		}

		else if (dynamic_cast<Entry_block*> (bb))
			statements->push_back (get_goto_next (bb, g));

		else if (dynamic_cast<Exit_block*> (bb))
			statements->push_back (new Label(labels[v]->clone ()));

		else if (dynamic_cast<Empty_block*> (bb))
		{
			statements->push_back (new Label(labels[v]->clone ()));
			statements->push_back (get_goto_next (bb, g));
		}
		else
			assert (0); // TODO branches
	}
};

class Label_counter : public Visitor
{
	map<string, int>* counts;
public:
	Label_counter (map<string, int>* c) : counts(c) {}

	void pre_label_name (LABEL_NAME* in)
	{
		(*counts)[*in->value]++;
	}
};

List<Statement*>*
CFG::get_linear_statements ()
{
	Linearizer linearizer;
	depth_first_search (bs, visitor (linearizer));
	List<Statement*>* results = linearizer.statements;

	/* Remove redundant gotos, which would fall-through to their targets
	 * anyway. */
	List<Statement*>::iterator i = results->begin ();
	while (i != results->end ())
	{
		Wildcard<LABEL_NAME>* ln = new Wildcard<LABEL_NAME>;
		Statement* s = *i;
		Statement* next = *(++i);
		if (s->match (new Goto (ln))
			&& next->match (new Label (ln->value)))
		{
			i--;

			// Use this form of looping so that the iterator moves to the next
			// iterm before its invalidated.
			results->erase (i++);
		}
	}

	/* Remove labels that are only used once. */
	map<string, int> label_counts;
	(new Label_counter (&label_counts))->visit_statement_list (results);

	i = results->begin ();
	while (i != results->end ())
	{
		Wildcard<LABEL_NAME>* ln = new Wildcard<LABEL_NAME>;
		if ((*i)->match (new Label (ln))
			&& label_counts[*ln->value->value] == 1)
			results->erase (i++);
		else
			i++;
	}

	return results;
}

