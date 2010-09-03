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
#include <boost/algorithm/string/replace.hpp>

#include "process_ast/DOT_unparser.h"
#include "process_ir/General.h"
#include "lib/escape.h"
#include "lib/Vector.h"

#include "CFG.h"
#include "Def_use_web.h"

#include "ssa/Dominance.h"

using namespace boost;
using namespace std;
using namespace MIR;

CFG::CFG (Method_info* info, Method* method)
: dominance (NULL)
, duw (NULL)
, method (method)
, method_info (info)
{
	vb = get(vertex_bb_t(), bs);
	ee = get(edge_cfg_edge_t(), bs);
	index = get(vertex_index_t(), bs);

	// Initialize the entry and exit blocks
	entry = add_bb (new Entry_block (this, method));
	// TODO should this be cloned? It means we can use the variables in it. It
	// also breaks the link between the entry and exit block, which wont exist
	// for cloned blocks.
	exit = add_bb (new Exit_block (this, method));

	add_statements (method->statements);

	clean ();

	// We use this for debugging
	renumber_vertex_indices ();

	dominance = new Dominance (this);
	dominance->calculate_forward_dominance ();
	dominance->calculate_reverse_dominance ();
}

// Used for cloning
/*CFG::CFG ()
: dominance (NULL)
, duw (NULL)
, method (NULL)
{
}*/

CFG::CFG (Graph& bs)
: dominance (NULL)
, duw (NULL)
, bs (bs)
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
	std::pair<edge_t,bool> pair = boost::add_edge (source->vertex, target->vertex, bs);

	// The graph should allow parallel edges.
	assert (pair.second);

	edge_t e = pair.first;
	ee[e] = new Edge (this, e);
	return ee[e];
}

pair<Edge*, Edge*>
CFG::add_branch (Branch_block* source, Basic_block* target1, Basic_block* target2)
{
	assert (source);
	std::pair<edge_t,bool> true_pair = boost::add_edge (source->vertex, target1->vertex, bs);
	std::pair<edge_t,bool> false_pair = boost::add_edge (source->vertex, target2->vertex, bs);

	// The graph should allow parallel edges.
	assert (true_pair.second);
	assert (false_pair.second);

	edge_t et = true_pair.first;
	edge_t ef = false_pair.first;

	ee[et] = new Edge (this, et, true);
	ee[ef] = new Edge (this, ef, false);

	return make_pair (ee[et], ee[ef]);
}

void
CFG::add_statements (Statement_list* statements)
{
	// Keep track of labels, for edges between gotos and branches.
	Map <string, vertex_t> labels;

	// In the second pass, we'll need the vertices to add edges.
	Map <Statement*, vertex_t> nodes;


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
	// The exit block can be missing, if there is no path to it (say, an
	// infinite loop).
	assert (exit != NULL);

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
class Depth_first_list : public default_dfs_visitor, virtual public GC_obj
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


#define FIELD_SEPARATOR " | "

static String*
escape_portname (String* in)
{
	foreach (char& ch, *in)
	{
		switch (ch)
		{
			case '[':
			case ']':
			case '$':
			case ':':
			case '=':
			case '/':
			case '-':
			case '*':
				ch = '_';
				break;
			default:
				break;
		}
	}
	return in;
}

String*
CFG::get_graphviz_def_portname (Basic_block* bb, SSA_name* def)
{
	stringstream ss;
	ss
	<< "def_" << *escape_portname (s (def->str ()))
	;
	return s (ss.str ());
}

String*
CFG::get_graphviz_phi_portname (Basic_block* bb, SSA_name* phi)
{
	stringstream ss;
	ss
	<< "phi_" << *escape_portname (s (phi->str ()))
	;
	return s (ss.str ());
}

String*
CFG::get_graphviz_use_portname (Basic_block* bb, SSA_name* use)
{
	stringstream ss;
	ss
	<< "use_" << bb->get_index () 
	<< "_" << *escape_portname (s (use->str()))
	;
	return s (ss.str ());
}

String*
CFG::get_graphviz_def (Basic_block* bb, SSA_name* def)
{
	stringstream ss;
	ss
	<< "<" << *get_graphviz_def_portname (bb, def) << "> "
	<< *escape_DOT_record (s (def->str ()))
	;
	return s (ss.str ());
}

String*
CFG::get_graphviz_use (Basic_block* bb, SSA_name* use)
{

	stringstream ss;
	ss
	<< "<" << *get_graphviz_use_portname (bb, use) << "> "
	<< *escape_DOT_record (s (use->str ()))
	;
	return s (ss.str ());
}
 
void
CFG::dump_graphviz (String* label)
{
  dump_graphviz(label, std::cout);
}

void
CFG::dump_graphviz (String* label, std::ostream &out)
{
	if (label == NULL) // for debugging
	{
		// The rest of the debug output goes to cerr, but this goes to cout, so
		// it can be redirected to dot.
		CHECK_DEBUG ();
		label = s ("TEST");
	}
	renumber_vertex_indices ();

	out
	<< "digraph G {\n"
	<< "graph [outputorder=edgesfirst];\n"
	<< "graph [labelloc=t];\n"
	<< "graph [label=\"CFG: " << *method->signature->method_name->value << " - " << *label << "\"];\n";

	// Nodes for Basic Blocks
	foreach (Basic_block* bb, *get_all_bbs ())
	{
		int index = bb->get_index ();
		
		// BB source
		stringstream block_info;
		if (duw)
		{
			Set<SSA_name>* phis = duw->get_phi_lhss (bb);
		
			if (phis -> size () )
			{
				foreach (SSA_name phi, *phis)
				{
					block_info << phi.str () << " = phi(";
					bool first=true;
					foreach(SSA_name* rhs, *duw->get_phi_args(bb,phi))
					{

						if(!first)
						{
							block_info << ",";
						}
						first=false;
						block_info << rhs->get_version ();
						
					}
					block_info << ")\\n";
				}
				block_info << "\\n";
			}
		}

		block_info	
		<< "(" << bb->ID << ") "
		<< *escape_DOT_record (bb->get_graphviz_label ()) << "\\n";

		// Print sigma functions.
		if (duw) {
			block_info << "\\n";

			Set<SSA_name> *sigmas = duw->get_sigma_rhss(bb);
			if (sigmas->size() > 0) {
				foreach (SSA_name sigma, *sigmas) {
					block_info << "sigma(";

					bool first = true;
					foreach (SSA_name *rhs, *duw->get_sigma_args(bb, sigma)) {
						if (!first) {
							block_info << ",";
						}

						first = false;
						block_info << rhs->get_version();
					}

					block_info << ") = " << sigma.str() << "\\n";
				}

				block_info << "\\n";
			}
		}

#define CFG_PENWIDTH "penwidth=\"2.0\""
		
		out
		<< index
		<< " [shape="
		<< (isa<Branch_block> (bb) ? "Mrecord" : "record") // branches are rounded
		<< ","
		<< CFG_PENWIDTH << ","
		<< "label=\"{"; // arrange fields vertically

		out << "\\n" << block_info.str ();

		// DUW nodes are fields in the BB
		if (duw)
		{
			SSA_name_list* defs = duw->get_defs (bb);
			SSA_name_list* uses = duw->get_uses (bb);
			SSA_name_list* may_defs = duw->get_may_defs(bb);	

			if (defs->size() || uses->size () || may_defs->size ())
			{
				// open dual columns
				out << FIELD_SEPARATOR << "{ { ";
				bool first = true;

				foreach (SSA_name* may_def, *may_defs)
				{
					out
					<< (first ? "" : FIELD_SEPARATOR) // no field separate
					<< *get_graphviz_def (bb, may_def) << " (May Def)";

					first = false;
				}

				foreach (SSA_name* def, *defs)
				{
					out
					<< (first ? "" : FIELD_SEPARATOR) // no field separate
					<< *get_graphviz_def (bb, def) << " (Def)";

					first = false;
				}

				// open second column
				out << " } " << FIELD_SEPARATOR <<  " { ";
				first = true;
				foreach (SSA_name* use, *uses)
				{
					out
					<< (first ? "" : FIELD_SEPARATOR)
					<< *get_graphviz_use (bb, use) << " (Use)";

					first = false;
				}

				// close dual columns
				out << " } } ";
			}
		}


		out << "}\"];\n";

		// DUW edges
		//Currently messing up a bit, left it commented out for now
		if (duw)
		{
			// Add an edge from each use to each def (there can be more than 1 in
			// non-SSA form)
/*			foreach (SSA_use* use, *duw->get_block_uses (bb))
			{
				foreach (SSA_def* def, *use->get_defs ())
				{
					cout 
					<< index << ":"
					<< *get_graphviz_use_portname (bb, use->name) << ":e"
					<< " -> "
					<< def->bb->get_index() << ":"
					<< *get_graphviz_def_portname (def->bb, def->name) << ":w"
					<< " [color=lightgrey,dir=both];\n"
					;
				}
			}*/
		}
	}

	// Edges
	foreach (Edge* edge, *get_all_edges ())
	{
		out
		<< edge->get_source()->get_index() 
		<< " -> "
		<< edge->get_target()->get_index ()
		<< "["
		<< CFG_PENWIDTH << ",";

		if (! indeterminate (edge->direction))
		{
			if (edge->direction)
				out << "label=T";
			else
				out << "label=F";
		}

		out << "];\n";
	}

	out << "}\n\n";
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

		if (!isa<Exit_block> (bb))
			assert (bb->get_successors ()->size () > 0);


		// Check phi nodes
		foreach (SSA_name phi_lhs, *bb->get_phi_lhss ())
		{
			assert (bb->get_phi_args (phi_lhs)->size () == bb->get_predecessors ()->size ());
			foreach (Edge* pred, *bb->get_predecessor_edges ())
				bb->get_phi_arg_for_edge (pred, phi_lhs);
		}

		// Check sigma nodes.
		foreach (SSA_name sigma_rhs, *bb->get_sigma_rhss ()) {
			assert (bb->get_sigma_args(sigma_rhs)->size () == 2);
			foreach (Edge *succ, *bb->get_successor_edges())
				bb->get_sigma_arg_for_edge(succ, sigma_rhs);
		}
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
class Linearizer : public default_dfs_visitor, virtual public GC_obj
{
	CFG* cfg;
	// Since the linearizer is passed by copy, a non-pointer would be
	// deallocated after the depth-first-search. However, we need to keep the
	// exit_label alive.
	Map<vertex_t, LABEL_NAME*>* labels;

public:

	List<Statement*>* statements;
	Linearizer(CFG* cfg) : cfg(cfg)
	{
		statements = new List<Statement*>;
		labels = new Map<vertex_t, LABEL_NAME*>;
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

class Label_counter : public Visitor, virtual public GC_obj
{
	Map<string, int>* counts;
public:
	Label_counter (Map<string, int>* c) : counts(c) {}

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
	Map<string, int> label_counts;
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
		foreach (Basic_block* replacement, *replacements)
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

	// Copy the properties (The edges don't change, so they're fine)
	new_bb->copy_phi_nodes (bb);

	consistency_check ();

	return new_bb;
}

void
CFG::remove_bb (Basic_block* bb)
{
	consistency_check ();

	// dont-care
	if (isa<Empty_block> (bb))
		return;

	replace_bb_with_empty (bb);

	consistency_check ();
}

void
CFG::remove_branch (Branch_block* branch, Basic_block* new_successor)
{
	consistency_check ();

	Edge* true_edge = branch->get_true_successor_edge ();
	Edge* false_edge = branch->get_false_successor_edge ();

	remove_edge (true_edge);
	remove_edge (false_edge);
	add_edge (branch, new_successor);

	replace_bb_with_empty (branch);

	consistency_check ();
}

void
CFG::rip_bb_out (Basic_block* bb)
{
	assert (!isa<Entry_block> (bb));

	boost::clear_vertex (bb->vertex, bs);
	boost::remove_vertex (bb->vertex, bs);

	// We need to be able to model CFGs with no exit block. These CFGs cannot
	// have post-dominance, however, due to an implementation issue.
	if (isa<Exit_block> (bb))
	{
		exit = NULL;
	}
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
	consistency_check ();

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
CFG::split_block (Basic_block* bb)
{
	assert (bb->get_predecessors ()->size() > 1);

	// This is much easier if there are no phis
	assert (bb->get_phi_lhss ()->size () == 0);

	foreach (Edge* edge, *bb->get_predecessor_edges ())
	{
		Basic_block* copy = bb->clone ();
		add_bb (copy);
		CTS ("num_branches_before");		

		Edge* new_edge = add_edge (edge->get_source (), copy);
		new_edge->direction = edge->direction;
		remove_edge (edge);

		foreach (Edge* succ, *bb->get_successor_edges ())
		{
			Edge* new_edge = add_edge (copy, succ->get_target ());
			new_edge->direction = succ->direction;
		}
	}
}


void
CFG::remove_edge (Edge* edge)
{
	boost::remove_edge (edge->edge, bs);
}


struct filter_back_edges : virtual public GC_obj
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
	Vector<vertex_t> vertices;
	topological_sort(fg, back_inserter(vertices), color_map(cm));

	// Convert to a list of BBs
	BB_list* result = new BB_list;
	foreach (vertex_t v, vertices)
	{
		result->push_front (vb[v]);
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
CFG::clean ()
{
	consistency_check ();

	// Iterate until the number of nodes and edges fix-points.
	unsigned int last_node_count;
	unsigned int last_edge_count;
	do
	{
		last_node_count = get_all_bbs ()->size();
		last_edge_count = get_all_edges ()->size();

		remove_unreachable_blocks ();
		fold_redundant_branches ();
		remove_empty_blocks ();
	}
	while (	last_node_count != get_all_bbs ()->size()
			|| last_edge_count != get_all_edges ()->size());


	consistency_check ();
}

void
CFG::remove_unreachable_blocks ()
{
	Set<Basic_block*> reachable;

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
			// Even if its an exit block!
			rip_bb_out (bb);
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

	foreach (Basic_block* bb, *get_all_bbs ())
	{
		if (Empty_block* eb = dynamic_cast<Empty_block*> (bb))
		{
			// There can be multiple predecessors, but only 1 successor.
			Basic_block* succ = eb->get_successor ();
			Edge* succ_edge = eb->get_successor_edge ();

			// Dont remove infinite loops (unless they're unreachable, but thats
			// handled in remove_unreachable_blocks.
			if (succ == eb)
				continue;

			// If the successor has another predeccessor, how will we know what
			// to put in the phi node (BB's phi node, that is, once its moved to
			// the successor)? Leave it in, it can be removed when the phi nodes
			// are dropped.
			if (succ->get_predecessors ()->size () > 1 && bb->get_phi_lhss ()->size () > 0)
				continue;


			// Merge the phi nodes into the next block.
			succ->copy_phi_nodes (eb);

			foreach (Basic_block* pred, *bb->get_predecessors ())
			{
				Edge* pred_edge = get_edge (pred, eb);

				// Add edge and copy attributes
				Edge* new_edge = add_edge (pred, succ);
				new_edge->direction = pred_edge->direction;
				new_edge->copy_phi_map (pred_edge);
				new_edge->copy_phi_map (succ_edge);

				// If there are more than 1 edges with the
				// same source and target (ie from a branch), then we run the
				// risk of getting the same edge more than once. If that happens,
				// we'll give the same direction to both edges, which is wrong.
				// To avoid this, remove the edge once we've added the new one.
				remove_edge (pred_edge);
			}

			rip_bb_out (eb);
		}
	}
}

CFG*
CFG::clone ()
{
	// The simplest way to create the graph is to create all the basic blocks,
	// then join them together. For equality, we can just check all the nodes
	// and all the edges are equal.

	// Clone the graph structure
	CFG* clone = new CFG (bs);
	clone->method = method->clone ();

	// Clone the blocks themselves
	foreach (vertex_t v, vertices (clone->bs))
	{
		clone->vb[v] = clone->vb[v]->clone ();
		clone->vb[v]->vertex = v;
		clone->vb[v]->cfg = clone;
	}

	foreach (edge_t e, edges (clone->bs))
	{
		clone->ee[e] = clone->ee[e]->clone ();
		clone->ee[e]->edge = e;
		clone->ee[e]->cfg = clone;
	}

	return clone;
}

bool
CFG::equals (CFG* other)
{
	// All the vertices should be numbered the same. Get easy access to
	// OTHER's numbering.
	Map<long, Basic_block*> others;
	foreach (Basic_block* bb, *other->get_all_bbs ())
	{
		others[bb->get_index()] = bb;
	}

	foreach (Basic_block* bb, *this->get_all_bbs ())
	{
		Basic_block* other_bb = others[bb->get_index ()];
		// Check the blocks are equals
		if (!bb->equals (other_bb))
			return false;

		// check the edges go to the same place, and have the same properties.
		Edge_list* edges = bb->get_successor_edges ();
		Edge_list* other_edges = other_bb->get_successor_edges ();

		// First case: 1 edge
		if (edges->size () == 1)
		{
			Basic_block* target = edges->front()->get_target ();
			Basic_block* other_target = other_edges->front()->get_target ();
			if (target->get_index() != other_target->get_index ())
				return false;
		}
		else if (edges->size () == 2)
		{
			// Must be a branch block
			Branch_block* br = dyc<Branch_block> (bb);
			Branch_block* other_br = dyc<Branch_block> (other_bb);

			Basic_block* true_target = br->get_true_successor ();
			Basic_block* other_true_target = other_br->get_true_successor ();
			if (true_target->get_index() != other_true_target->get_index ())
				return false;

			Basic_block* false_target = br->get_false_successor ();
			Basic_block* other_false_target = other_br->get_false_successor ();
			if (false_target->get_index() != other_false_target->get_index ())
				return false;
		}
		else
		{
			assert (edges->size () == 0);
		}
	}

	return true;
}
