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
#include "Def_use.h"
#include "process_ast/DOT_unparser.h"
#include "process_ir/General.h"

using namespace boost;
using namespace std;
using namespace MIR;

CFG::CFG (Method* method)
: dominance (NULL)
, duw (NULL)
, bs()
, method (method)
{
	vb = get(vertex_bb_t(), bs);
	ee = get(edge_cfg_edge_t(), bs);
	index = get(vertex_index_t(), bs);

	// Initialize the entry and exit blocks
	entry = add_bb (new Entry_block (this, method));
	exit = add_bb (new Exit_block (this, method));

	add_statements (method->statements);

	clean ();
}

CFG::CFG (Graph& bs)
: dominance (NULL)
, duw(NULL)
, bs(bs)
, method (NULL)
{
}

vertex_t
CFG::add_bb (Basic_block* bb)
{
	assert (bb->vertex == NULL);

	vertex_t v = add_vertex (bs);
	vb[v] = bb;
	bb->vertex = v;

	return v;
}

Edge*
CFG::add_edge (Basic_block* source, Basic_block* target)
{
	edge_t e = boost::add_edge (source->vertex, target->vertex, bs).first;
	ee[e] = new Edge (this, e);
	return ee[e];
}

pair<Edge*, Edge*>
CFG::add_branch (Branch_block* source, Basic_block* target1, Basic_block* target2)
{
	assert (source);
	edge_t et = boost::add_edge (source->vertex, target1->vertex, bs).first;
	edge_t ef = boost::add_edge (source->vertex, target2->vertex, bs).first;

	ee[et] = new Edge (this, et, true);
	ee[ef] = new Edge (this, ef, false);

	return make_pair (ee[et], ee[ef]);
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

			case Return::ID:
			{
				add_edge (vb[v], vb[exit]);
				use_parent = false;
				break;
			}

			default:
				parent = v;
				use_parent = true;
				break;
		}
	}

	// Return adds the edge already.
	if (use_parent)
		add_edge (vb[parent], vb[exit]);

	consistency_check ();
}

Entry_block*
CFG::get_entry_bb ()
{
	return dyc<Entry_block> (vb[entry]);
}

Exit_block*
CFG::get_exit_bb ()
{
	return dyc<Exit_block> (vb[exit]);
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
	property_map<Graph, edge_cfg_edge_t>::type ee;
	property_map<Graph, vertex_index_t>::type index;

	BB_property_functor (CFG* cfg)
	{
		vb = cfg->vb;
		ee = cfg->ee;
		index = cfg->index;
	}
	void operator()(std::ostream& out, const edge_t& e) const 
	{
		Edge* edge = ee[e];
		if (indeterminate (edge->direction))
			return;

		if (edge->direction)
			out << "[label=T]";
		else
			out << "[label=F]";

		// Head and tail annotatations are done in the vertex, because the
		// headlabel and taillabel attributes dont expand the area they are
		// in, and so are frequently unreadable.
	}
#define LINE_LENGTH 20
	void operator()(std::ostream& out, const vertex_t& v) const 
	{
		out << "[";

		pair<String*, String*> bb_props;
		foreach (bb_props, *vb[v]->get_graphviz_properties ())
			out << *bb_props.first << "=" << *bb_props.second << ",";

		out << "label=\"";

		// IN annotations
		stringstream ss1;
		pair<String*, list<String*> > props;
		foreach (props, *vb[v]->get_graphviz_head_properties ())
		{
			if (props.second.size ())
			{
				ss1 << *props.first << " = [";
				unsigned int line_count = 1;
				foreach (String* str, props.second)
				{
					ss1 << *DOT_unparser::escape (str) << ", ";
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
		ss2
			<< "(" << index[v] << ") "
			<< *DOT_unparser::escape (vb[v]->get_graphviz_label ());

		// BB properties
		stringstream ss3;
		foreach (props, *vb[v]->get_graphviz_bb_properties ())
		{
			if (props.second.size ())
			{
				ss3 << *props.first << " = [";
				unsigned int line_count = 1;
				foreach (String* str, props.second)
				{
					ss3 << *str << ", ";
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
			if (props.second.size ())
			{
				ss4 << *props.first << " = [";
				unsigned int line_count = 1;
				foreach (String* str, props.second)
				{
					ss4 << *str << ", ";
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
	if (label == NULL) // for debugging
	{
		// The rest of the debug output goes to cerr, but this goes to cout, so
		// it can be redirected to dot.
		CHECK_DEBUG ();
		label = s ("TEST");
	}
	renumber_vertex_indices ();
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
	foreach (vertex_t v, vertices (bs))
	{
		Basic_block* bb = vb[v];

		// The graph should never reuse vertices.
		assert (bb->vertex == v);

		// Check phi nodes
		foreach (VARIABLE_NAME* phi_lhs, *bb->get_phi_lhss())
		{
			assert (bb->get_phi_args (phi_lhs)->size () == bb->get_predecessors ()->size ());
			foreach (Edge* pred, *bb->get_predecessor_edges ())
				bb->get_phi_arg_for_edge (pred, phi_lhs);
		}

		if (!isa<Exit_block> (bb))
			assert (bb->get_successors ()->size () > 0);
	}

	foreach (edge_t e, edges (bs))
	{
		Edge* edge = ee[e];
		assert (edge->edge == e);

		// Directions should only follow branches
		if (edge->direction != indeterminate)
			assert (isa<Branch_block>(edge->get_source ()));
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
	dominance->calculate_forward_dominance ();
	dominance->calculate_reverse_dominance ();
	dominance->dump ();

	// Build def-use web (we're not in SSA form, but this will do the job).
	duw = new Def_use_web ();
	duw->run (this);

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
			// Get defs (including phi node LHSs)
			VARIABLE_NAME_list* def_list = bb->get_pre_ssa_defs ();
			foreach (VARIABLE_NAME* phi_lhs, *bb->get_phi_lhss())
				def_list->push_back (phi_lhs);

			bool def_added = false;
			foreach (VARIABLE_NAME* var_name, *def_list)
			{
				if (!frontier->has_phi_node (var_name))
				{
					frontier->add_phi_node (var_name);
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

	// Check all variables are converted
	class Check_in_SSA : public Visitor
	{
		void pre_variable_name (VARIABLE_NAME* in)
		{
			assert (in->in_ssa);
		}
	};

	foreach (Basic_block* bb, *get_all_bbs ())
	{
		if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
			sb->statement->visit (new Check_in_SSA ());
	}

	consistency_check ();

	// Build def-use web
	duw = new Def_use_web ();
	duw->run (this);
}

void
CFG::rebuild_ssa_form ()
{
	clean ();
	consistency_check ();

	dominance = new Dominance (this);
	dominance->calculate_forward_dominance ();
	dominance->calculate_reverse_dominance ();

	duw = new Def_use_web ();
	duw->run (this);
}


void
CFG::convert_out_of_ssa_form ()
{
	foreach (Basic_block* bb, *get_all_bbs ())
	{
		foreach (VARIABLE_NAME* phi_lhs, *bb->get_phi_lhss ())
		{
			BB_list* preds = bb->get_predecessors ();
			foreach (Rvalue* rval, *bb->get_phi_args (phi_lhs))
			{
				Assign_var* copy = new Assign_var (
					phi_lhs->clone (),
					false,
					rval->clone ());

				Statement_block* new_bb = new Statement_block (this, copy);

				insert_bb_between (get_edge (preds->front (), bb), new_bb);
				// TODO I'm not sure these are in the same order.
				// - the edge is included in the phi node, so use it.
				preds->pop_front ();

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

Edge*
CFG::get_edge (Basic_block* bb1, Basic_block* bb2)
{
	foreach (edge_t e, out_edges (bb1->vertex, bs))
		if (target (e, bs) == bb2->vertex)
			return ee[e];

	assert (0);
}

Edge*
CFG::get_entry_edge ()
{
	return get_entry_bb ()->get_successor_edge ();
}

Edge_list*
CFG::get_all_edges ()
{
	Edge_list* result = new Edge_list;

	foreach (edge_t e, edges(bs))
	{
		result->push_back (ee[e]);
	}
	return result;
}

Edge_list*
CFG::get_edge_successors (Basic_block* bb)
{
	Edge_list* result = new Edge_list;

	foreach (edge_t e, out_edges (bb->vertex, bs))
	{
		result->push_back (ee[e]);
	}

	return result;
}

Edge_list*
CFG::get_edge_predecessors (Basic_block* bb)
{
	Edge_list* result = new Edge_list;

	foreach (edge_t e, in_edges (bb->vertex, bs))
	{
		result->push_back (ee[e]);
	}

	return result;
}

/* returns true or false. If edge isnt true or false, asserts. */
bool
CFG::is_true_edge (Edge* edge)
{
	assert (!indeterminate (edge->direction));
	return edge->direction;
}

// TODO:
//	A new plan for removing basic_blocks:
//	1) To remove a block, replace it with an empty block, with the same phi nodes
//	2) To replace a block, replace it with an empty block (with the phi nodes),
//		and follow it by the new BB.
//	3) To remove a branch, replace it with an empty block (same phis), and
//		require knowledge of the new target for the outgoing edge.
//	4) tidy_up will sort out the empty blocks, merging the phi nodes into
//		successor blocks if possible (it must be possible, i think).
//	5)	Look at Cooper/torczon Section 10.3


void
CFG::insert_predecessor_chain (Basic_block* bb, BB_list* new_bbs)
{
	foreach (Basic_block* new_bb, *new_bbs)
		insert_predecessor_bb (bb, new_bb);
}

void
CFG::replace_bb (Basic_block* bb, BB_list* replacements)
{
	consistency_check ();

	// Same BB: do nothing
	if (replacements->size() == 1
			&& replacements->front() == bb)
		return;

	if (replacements->size() == 0)
	{
		remove_bb (bb);
	}
	else if (bb == replacements->back ())
	{
		// Insert the new nodes without removing the old one. Replacing the old
		// one will invalidate the BB's vertex. (exit blocks dont like that).
		replacements->pop_back ();
		insert_predecessor_chain (bb, replacements);
	}
	else
	{
		// TODO: we dont support adding nodes before and after:
		foreach (Basic_block* replacement , *replacements)
			assert (bb != replacement);

		insert_predecessor_chain (bb, replacements);
		remove_bb (bb);
	}

	consistency_check ();
}

Empty_block*
CFG::replace_bb_with_empty (Basic_block* bb)
{
	// By replacing the BB, we ruin any information that stores BB*s.
	// Everything should use vertices instead, and update through this.
	
	consistency_check ();

	assert (bb->get_successors ()->size () == 1);

	// Replace it directly
	Empty_block* new_bb = new Empty_block (this);
	new_bb->vertex = bb->vertex;
	vb[bb->vertex] = new_bb;

	// Copy the properties (The edges are the same, so they'll auto-update)
	new_bb->copy_phi_nodes (bb);

	consistency_check ();

	return new_bb;
}

void
CFG::remove_bb (Basic_block* bb)
{
	// dont-care
	if (isa<Empty_block> (bb))
		return;

	replace_bb_with_empty (bb);
}

void
CFG::remove_branch (Branch_block* branch, Basic_block* new_successor)
{
	// ummmmm, what then?
	assert (new_successor->get_phi_lhss ()->size () == 0);

	remove_edge (branch->get_true_successor_edge ());
	remove_edge (branch->get_false_successor_edge ());
	add_edge (branch, new_successor);

	replace_bb_with_empty (branch);
}

void
CFG::rip_bb_out (Basic_block* bb)
{
	assert (!isa<Entry_block> (bb));
	assert (!isa<Exit_block> (bb));
	boost::clear_vertex (bb->vertex, bs);
	boost::remove_vertex (bb->vertex, bs);
}

void
CFG::insert_bb_between (Edge* edge, Basic_block* new_bb)
{
	add_bb (new_bb);

	Edge* pred_edge = add_edge (edge->get_source (), new_bb);
	pred_edge->direction = edge->direction;

	Edge* succ_edge = add_edge (new_bb, edge->get_target ());
	succ_edge->copy_phi_map (edge);

	remove_edge (edge);
}

void
CFG::insert_predecessor_bb (Basic_block* bb, Basic_block* new_bb)
{
	assert (!isa<Branch_block> (new_bb));
	assert (new_bb->get_phi_lhss()->size () == 0);

	// Assume this isnt added
	add_bb (new_bb);

	// Move the phi nodes
	new_bb->copy_phi_nodes (bb);
	bb->remove_phi_nodes ();

	// Connect to each predecessor
	foreach (Basic_block* pred, *bb->get_predecessors ())
	{
		Edge* old_edge = get_edge (pred, bb);

		Edge* new_edge = add_edge (pred, new_bb);
		new_edge->copy_phi_map (old_edge);

		remove_edge (old_edge);
	}

	// No phis or direction. Make sure to ad this after processing
	// predecessors, or this will be a predecessor of BB.
	add_edge (new_bb, bb);
}

void 
CFG::set_branch_direction (Branch_block* bb, bool direction)
{
	Edge* true_edge = bb->get_true_successor_edge ();
	Edge* false_edge = bb->get_false_successor_edge ();

	// Just remove the outgoing node
	if (direction)
	{
		true_edge->direction = indeterminate;
		remove_edge (false_edge);
	}
	else
	{
		false_edge->direction = indeterminate;
		remove_edge (true_edge);
	}

	// Update in place (takes care of incoming nodes)
	replace_bb_with_empty (bb);

	consistency_check ();
}


void
CFG::remove_edge (Edge* edge)
{
	boost::remove_edge (edge->edge, bs);
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



// TODO: iterate (use cooper/torczon Fig 10.5)
void
CFG::clean ()
{
	consistency_check ();

	remove_unreachable_blocks ();
	fix_solo_phi_args ();
	fold_redundant_branches ();
	remove_empty_blocks ();

	consistency_check ();
}

void
CFG::remove_unreachable_blocks ()
{
	set<Basic_block*> reachable;

	// Mark-sweep to remove unreachable nodes.
	BB_list* worklist = new BB_list(get_entry_bb ());

	while (worklist->size () > 0)
	{
		Basic_block* bb = worklist->front ();
		worklist->pop_front ();

		// Dont process BBs we've seen before
		if (reachable.find (bb) != reachable.end ())
			continue;

		// mark reachable
		reachable.insert (bb);
	
		// Add successors to the worklist
		foreach (Basic_block* succ, *bb->get_successors ())
			worklist->push_back (succ);
	}

	// remove all nodes not marked as reachable
	foreach (Basic_block* bb, *get_all_bbs ())
	{
		if (reachable.find (bb) == reachable.end ())
		{
			// TODO: this is definitely possible. What then?
			assert (!isa<Exit_block> (bb));

			// Dont just convert to an empty node. Rip it out entirely.
			rip_bb_out (bb);
		}
	}
}


/* Replace any phi node with a single argument with an assignment. */
void
CFG::fix_solo_phi_args ()
{
	foreach (Basic_block* bb, *get_all_bbs ())
	{
		// TODO: The theory is that each Phi node executes simultaneously. If
		// there are dependencies between the nodes, this could be wrong.
		// Simulateously means that the values are read before they are written
		// to. So there is a possible situation where:
		//		x0 = Phi (y0, ...)
		//		y0 = Phi (x0, ...)
		// in this case, neither ordering is correct, and temporary variables
		// must be used.

		// One edge means 1 phi argument
		if (bb->get_predecessor_edges()->size () == 1)
		{
			BB_list* new_bbs = new BB_list ();
			foreach (VARIABLE_NAME* phi_lhs, *bb->get_phi_lhss ())
			{
				Rvalue* arg = bb->get_phi_args (phi_lhs)->front ();
				new_bbs->push_back (
						new Statement_block (
							this,
							new Assign_var (
								phi_lhs->clone(),
								false,
								arg)));
			}

			// Remove the Phis before adding the predecessors. 
			bb->remove_phi_nodes ();

			insert_predecessor_chain (bb, new_bbs);
		}
	}
}

void
CFG::fold_redundant_branches ()
{
	// Cooper/Torczon, page 501, 1
	foreach (Basic_block* bb, *get_all_bbs ())
	{
		if (Branch_block* branch = dynamic_cast <Branch_block*> (bb))
		{
			if (branch->get_true_successor () == branch->get_false_successor ())
				set_branch_direction (branch, true);
		}
	}
}

void
CFG::remove_empty_blocks ()
{
	// cooper/torczon, page 501, 2

	// An empty BB might factor phi nodes between, say, 2 rather than 3 nodes.
	// In that case, removing them would lead to extra code in the
	// predecessors.
	foreach (Basic_block* bb, *get_all_bbs ())
	{
		if (Empty_block* eb = dynamic_cast<Empty_block*> (bb))
		{
			// There can be multiple predecessors, but only 1 successor.
			Basic_block* succ = eb->get_successor ();
			Edge* succ_edge = eb->get_successor_edge ();

			// Dont remove infinite loops (unless their unreachable, but thats
			// handled in remove_unreachable_blocks.
			if (succ == eb)
				continue;


			// Merge the phi nodes into the next block.
			succ->copy_phi_nodes (eb);

			foreach (Basic_block* pred, *bb->get_predecessors ())
			{
				Edge* pred_edge = get_edge (pred, bb);

				// Add edge and copy attributes
				Edge* new_edge = add_edge (pred, succ);
				new_edge->direction = pred_edge->direction;
				new_edge->copy_phi_map (succ_edge);
			}

			rip_bb_out (eb);
		}
	}
}
