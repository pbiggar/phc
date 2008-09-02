/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Control-flow Graph
 */

#include <boost/foreach.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/dominator_tree.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/topological_sort.hpp>

#include "CFG.h"
#include "SSA.h"
#include "process_ast/DOT_unparser.h"
#include "process_ir/General.h"

using namespace boost;
using namespace std;
using namespace MIR;

CFG::CFG (Method* method)
: dominance (NULL)
, bs()
, method (method)
{
	vb = get(vertex_bb_t(), bs);
	ebd = get(edge_branch_direction_t(), bs);
	index = get(vertex_index_t(), bs);

	// Initialize the entry and exit blocks
	entry = add_bb (new Entry_block (this, method));
	exit = add_bb (new Exit_block (this, method));

	add_statements (method->statements);
}

vertex_t
CFG::add_bb (Basic_block* bb)
{
	vertex_t v = add_vertex (bs);
	vb[v] = bb;
	bb->vertex = v;

	return v;
}

edge_t
CFG::add_edge (Basic_block* source, Basic_block* target)
{
	edge_t e = boost::add_edge (source->vertex, target->vertex, bs).first;
	ebd[e] = indeterminate;
	return e;
}

pair<edge_t, edge_t>
CFG::add_branch (Branch_block* source, Basic_block* target1, Basic_block* target2)
{
	assert (source);
	edge_t et = boost::add_edge (source->vertex, target1->vertex, bs).first;
	edge_t ef = boost::add_edge (source->vertex, target2->vertex, bs).first;

	ebd[et] = true;
	ebd[ef] = false;
	return pair<edge_t, edge_t> (et,ef);
}

void
CFG::add_statements (Statement_list* statements)
{
	// Keep track of labels, for edges between gotos and branches.
	map <string, vertex_t> labels;

	// In the second pass, we'll need the vertices to add edges.
	map <Statement*, vertex_t> nodes;


	// In the first pass, just create nodes for the statements.
	foreach (Statement* s, *statements)
	{
		vertex_t v;
		switch (s->classid())
		{
			case Label::ID:
				v = add_bb (new Empty_block (this));
				labels [*dyc<Label>(s)->label_name->get_value_as_string ()] = v;
				break;

			case Goto::ID:
				v = add_bb (new Empty_block (this));
				break;

			case Branch::ID:
				v = add_bb (new Branch_block (this, dyc<Branch>(s)));
				break;

			default:
				v = add_bb (new Statement_block (this, s));
				break;
		}
		nodes[s] = v;
	}


	// Create the edges
	vertex_t parent = entry;
	bool use_parent = true; // parent is just an int, so not nullable

	foreach (Statement* s, *statements)
	{
		// Be careful with pointers. Its very easy to overwrite vertices
		vertex_t v = nodes[s];
		if (use_parent)
			add_edge (vb[parent], vb[v]);

		switch (s->classid())
		{
			case Goto::ID:
			{
				vertex_t target = 
					labels[*dyc<Goto>(s)->label_name->get_value_as_string ()];
				add_edge (vb[v], vb[target]);

				use_parent = false;
				break;
			}

			case Branch::ID:
			{
				Branch* b = dyc<Branch>(s);
				vertex_t iftrue = labels[*b->iftrue->get_value_as_string ()];
				vertex_t iffalse = labels[*b->iffalse->get_value_as_string ()];
				add_branch (
					dynamic_cast<Branch_block*> (vb[v]),
					vb[iftrue],
					vb[iffalse]);

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
	add_edge (vb[parent], vb[exit]);

	tidy_up ();

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

BB_list*
CFG::get_all_bbs ()
{

	BB_list* result = new BB_list;

	foreach (vertex_t v, vertices(bs))
	{
		result->push_back (vb[v]);
	}

	return result;
}

// TODO simplify linearizer
template <class Graph>
class Depth_first_list : public default_dfs_visitor
{
public:
	BB_list* result;

	Depth_first_list (BB_list* result)
	: result (result)
	{
	}

	void discover_vertex (vertex_t v, const Graph& g)
	{
		result->push_back (get(vertex_bb_t(), g)[v]);
	}
};


// Dump to graphviz
struct BB_property_functor
{
	property_map<Graph, vertex_bb_t>::type vb;
	boost::property_map<Graph, edge_branch_direction_t>::type ebd;

	BB_property_functor (CFG* cfg)
	{
		vb = cfg->vb;
		ebd = cfg->ebd;
	}
	void operator()(std::ostream& out, const edge_t& e) const 
	{
		if (indeterminate (ebd[e]))
			return;

		if (ebd[e])
			out << "[label=T]";
		else
			out << "[label=F]";

		// Head and tail annotatations are done in the vertex, because the
		// headlabel and taillabel attributes dont expand the area they are
		// in, and so are frequently unreadable.
	}
#define LINE_LENGTH 30
	void operator()(std::ostream& out, const vertex_t& v) const 
	{
		out << "[";

		pair<String*, String*> bb_props;
		foreach (bb_props, *vb[v]->get_graphviz_properties ())
			out << *bb_props.first << "=" << *bb_props.second << ",";

		out << "label=\"";

		// IN annotations
		stringstream ss1;
		pair<String*, Set*> props;
		foreach (props, *vb[v]->get_graphviz_head_properties ())
		{
			if (props.second->size ())
			{
				ss1 << *props.first << " = [";
				unsigned int line_count = 1;
				foreach (VARIABLE_NAME* var_name, *props.second)
				{
					ss1 << *var_name->get_ssa_var_name() << ", ";
					if (ss1.str().size() > (LINE_LENGTH * line_count))
					{
						line_count++;
						ss1 << "\\n";
					}
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
			if (props.second->size ())
			{
				ss3 << *props.first << " = [";
				unsigned int line_count = 1;
				foreach (VARIABLE_NAME* var_name, *props.second)
				{
					ss3 << *var_name->get_ssa_var_name () << ", ";
					if (ss3.str().size() > (LINE_LENGTH * line_count))
					{
						line_count++;
						ss3 << "\\n";
					}
				}
				ss3 << "]\\n";
			}
		}

		// OUT annotations
		stringstream ss4;
		foreach (props, *vb[v]->get_graphviz_tail_properties ())
		{
			if (props.second->size ())
			{
				ss4 << *props.first << " = [";
				unsigned int line_count = 1;
				foreach (VARIABLE_NAME* var_name, *props.second)
				{
					ss4 << *var_name->get_ssa_var_name() << ", ";
					if (ss4.str().size() > (LINE_LENGTH * line_count))
					{
						line_count++;
						ss4 << "\\n";
					}
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
	String* method_name;
	Graph_property_functor(String* method_name, String* label) 
	: label (label)
	, method_name (method_name)
	{
	}

	void operator()(std::ostream& out) const 
	{
		out << "graph [outputorder=edgesfirst];" << std::endl;
		out << "graph [label=\"" << *method_name << " - " << *label << "\"];" << std::endl;
	}
};

void
CFG::dump_graphviz (String* label)
{
	renumber_vertex_indices ();
	consistency_check ();
	write_graphviz (
		cout, 
		bs, 
		BB_property_functor(this),
		BB_property_functor(this),
		Graph_property_functor(method->signature->method_name->value, label));
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
// Do a depth first search. For each block, add a label, and a goto to the
// next block(s).
class Linearizer : public default_dfs_visitor
{
	CFG* cfg;
	// Since the linearizer is passed by copy, a non-pointer would be
	// deallocated after the depth-first-search. However, we need to keep the
	// exit_label alive.
	map<vertex_t, LABEL_NAME*>* labels;

public:

	List<Statement*>* statements;
	Linearizer(CFG* cfg) : cfg(cfg)
	{
		statements = new List<Statement*>;
		labels = new map<vertex_t, LABEL_NAME*>;
	}

	/* Assign a label for each block. */
	void initialize_vertex (vertex_t v, const Graph& g)
	{
		(*labels) [v] = fresh_label_name ();
	}

	void discover_vertex (vertex_t v, const Graph& g)
	{
		Basic_block* bb = get(vertex_bb_t(), g)[v];

		// Add a label (the exit block label is added at the very end)
		if (not dynamic_cast<Exit_block*> (bb))
			statements->push_back (new Label((*labels)[v]->clone ()));

		// Statement or branch block
		if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
			statements->push_back (sb->statement);

		else if (Branch_block* br = dynamic_cast<Branch_block*> (bb))
		{
			// While in the CFG, the ifftrue and iffalse fields of a branch are
			// meaningless (by design).
			statements->push_back (br->branch);
			br->branch->iftrue = (*labels)[br->get_true_successor ()->vertex];
			br->branch->iffalse = (*labels)[br->get_false_successor ()->vertex];
		}

		// Add a goto successor
		if (not dynamic_cast<Branch_block*> (bb)
				&& not dynamic_cast<Exit_block*> (bb))
		{
			vertex_t next = bb->get_successor ()->vertex;
			statements->push_back (new Goto ((*labels)[next]->clone ()));
		}
	}

	void add_exit_label ()
	{
		Basic_block* bb = cfg->get_exit_bb ();

		// Add an exit block at the very end, so that it doesnt fall through to
		// anything.
		statements->push_back (new Label((*labels)[bb->vertex]->clone ()));
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
	Linearizer linearizer (this);
	renumber_vertex_indices ();
	depth_first_search (bs, visitor (linearizer));
	linearizer.add_exit_label ();
	List<Statement*>* results = linearizer.statements;

	/* Remove redundant gotos, which would fall-through to their targets
	 * anyway. */
	List<Statement*>::iterator i = results->begin ();
	List<Statement*>::iterator end = --results->end ();
	while (i != end) // stop one before the end, so that i++ will still read a statement
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


void
CFG::renumber_vertex_indices ()
{
	int new_index = 0;
	foreach (vertex_t v, vertices (bs))
		index[v] = new_index++;
}


/* SSA from here */

void CFG::convert_to_ssa_form ()
{
	// Calculate dominance frontiers
	dominance = new Dominance (this);
	dominance->calculate_immediate_dominators ();
	dominance->calculate_local_dominance_frontier ();
	dominance->propagate_dominance_frontier_upwards ();

	// Muchnick gives up at this point. We continue instead in Cooper/Torczon,
	// Section 9.3.3, with some minor changes. Since we dont have a list of
	// global names, we iterate through all blocks, rather than the blocks
	// corresponding to the variable names. 
	
	// For an assignment to X in BB, add a PHI function for variable X in the
	// dominance frontier of BB.
	// TODO Abstract this.
	BB_list* worklist = get_all_bbs_top_down ();
	BB_list::iterator i = worklist->begin ();
	while (i != worklist->end ())
	{
		Basic_block* bb = *i;
		foreach (Basic_block* frontier, *bb->get_dominance_frontier ())
		{
			bool def_added = false;
			// TODO defs include Phi functions.
			foreach (VARIABLE_NAME* var_name, *bb->get_ssa_defs ())
			{
				if (!frontier->has_phi_function (var_name))
				{
					frontier->add_phi_function (var_name);
					def_added = true;
				}
			}

			// This adds a new def, which requires us to iterate.
			if (def_added)
				worklist->push_back (frontier);
		}
		i++;
	}

	SSA_renaming sr(this);
	sr.rename_vars (get_entry_bb ());
}


void
CFG::convert_out_of_ssa_form ()
{
	// TODO
	foreach (Basic_block* bb, *get_all_bbs ())
	{
		foreach (Phi* phi, *bb->get_phi_nodes ())
		{
			foreach (VARIABLE_NAME* var_name, *phi->args)
			{
				Assign_var* copy = new Assign_var (
					phi->lhs->clone (),
					false,
					var_name->clone ());

				Statement_block* new_bb = new Statement_block (this, copy);

				// TODO get the real predecessor.
				add_bb_between (bb->get_predecessors ()->front (), bb, new_bb);

				// We avoid the critical edge problem because we have only 1
				// statement per block. Removing phi nodes adds a single block
				// along the necessary edge.
			}
		}
		bb->remove_phi_nodes ();
	}

	// TODO: at this point, we could do with a register-allocation style
	// interference graph to reduce the number of temporaries (aka
	// "registers") that we use in the generated code.
}

BB_list*
CFG::get_bb_successors (Basic_block* bb)
{
	BB_list* result = new BB_list;

	foreach (edge_t e, out_edges (bb->vertex, bs))
	{
		result->push_back (vb[target (e, bs)]);
	}

	return result;
}

BB_list*
CFG::get_bb_predecessors (Basic_block* bb)
{
	BB_list* result = new BB_list;

	foreach (edge_t e, in_edges (bb->vertex, bs))
	{
		result->push_back (vb[source (e, bs)]);
	}

	return result;
}

edge_t
CFG::get_edge (Basic_block* bb1, Basic_block* bb2)
{
	foreach (edge_t e, out_edges (bb1->vertex, bs))
		if (target (e, bs) == bb2->vertex)
			return e;

	assert (0);
}

/* returns true or false. If edge isnt true or false, asserts. */
bool
CFG::is_true_edge (edge_t edge)
{
	assert (!indeterminate (ebd[edge]));
	return ebd[edge];
}

void
CFG::add_bb_between (Basic_block* source, Basic_block* target, Basic_block* new_bb)
{
	add_bb (new_bb);
	edge_t current_edge = get_edge (source, target);
	assert (indeterminate (ebd[current_edge])); // TODO
	add_edge (source, new_bb);
	add_edge (new_bb, target);
	remove_edge (current_edge, bs);
}


void
CFG::replace_bb (Basic_block* bb, BB_list* replacements)
{
	// If the edge has a T/F label, it is because the predecessor is a Branch.
	// Just copy the label from the new predecessor.

	if (replacements->size() == 1
		&& replacements->front() == bb)
	{
		// Same BB: do nothing
	}
	else if (replacements->size() == 0)
	{
		// Remove the BB
		foreach (Basic_block* pred, *bb->get_predecessors ())
			foreach (Basic_block* succ, *bb->get_successors ())
			{
				edge_t e = add_edge (pred, succ);
				ebd[e] = ebd[get_edge (pred, bb)];
			}

		remove_bb (bb);
	}
	else
	{
		// TODO This should create a chain, and add an edge to the front and
		// back. I suspect this doesnt work.
		assert (0);
		foreach (Basic_block* new_bb, *replacements)
		{
			add_bb (new_bb);

			// Add edges from predecessors
			foreach (Basic_block* pred, *bb->get_predecessors ())
			{
				add_edge (pred, new_bb);
			}

			// Add edges from successors 
			foreach (Basic_block* succ, *bb->get_successors ())
			{
				add_edge (new_bb, succ);
			}
		}
		remove_bb (bb);
	}
}

void
CFG::remove_bb (Basic_block* bb)
{
	clear_vertex (bb->vertex, bs);
	remove_vertex (bb->vertex, bs);
}



struct filter_back_edges
{
	CFG* cfg;

	filter_back_edges () {}

	filter_back_edges (CFG* cfgs)
	: cfg (cfg)
	{
	}

	template <typename Edge>
	bool operator()(const Edge& e) const
	{
		// back edges have a gray target.
		return gray_color != cfg->cm[target(e, cfg->bs)];
	}
};

BB_list*
CFG::get_all_bbs_top_down ()
{
	typedef filtered_graph<Graph, filter_back_edges> DAG;

	renumber_vertex_indices ();

	// Create a new graph, without back edges.
	DAG fg (bs, filter_back_edges (this));

	// Do a topologic sort on the graph.
	vector<vertex_t> vertices;
	topological_sort(fg, back_inserter(vertices), color_map(cm));

	// Convert to a list of BBs
	BB_list* result = new BB_list;
	foreach (vertex_t v, vertices)
	{
		result->push_back (vb[v]);
	}

	return result;
}

BB_list*
CFG::get_all_bbs_bottom_up ()
{
	BB_list* result = get_all_bbs_top_down ();
	result->reverse ();
	return result;
}

void
CFG::tidy_up ()
{
	foreach (Basic_block* bb, *get_all_bbs ())
	{
		// Remove unreachable blocks (ie, no predecessors and are not the entry
		// block).
	
		// Remove empty blocks (have either 1 predecessor or 1 successor).
		if (isa<Empty_block> (bb))
			bb->remove ();


	}
}
