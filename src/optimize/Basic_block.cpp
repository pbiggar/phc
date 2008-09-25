#include "process_ir/General.h"
#include "process_mir/MIR_unparser.h"
#include "MIR.h"

#include "Basic_block.h"
#include "Def_use.h"

using namespace std;
using namespace MIR;

/* Constructors */

Basic_block::Basic_block(CFG* cfg)
: cfg(cfg)
, vertex (NULL)
, defs (NULL)
, uses (NULL)
, live_in (NULL)
, live_out (NULL)
, changed (false)
, aliases (NULL)
{
}

Branch_block::Branch_block (CFG* cfg, MIR::Branch* b)
: Basic_block (cfg)
, branch (b) 
{
}

Statement_block::Statement_block (CFG* cfg, MIR::Statement* s) 
: Basic_block (cfg)
, statement(s)
{
}

Empty_block::Empty_block (CFG* cfg)
: Basic_block (cfg)
{
}

Entry_block::Entry_block (CFG* cfg, Method* method)
: Basic_block (cfg)
, method (method)
{
}

Exit_block::Exit_block (CFG* cfg, Method* method)
: Basic_block (cfg)
, method (method)
{
}

list<pair<String*,String*> >*
Basic_block::get_graphviz_properties ()
{
	list<pair<String*,String*> >* result = new list<pair<String*,String*> >;
	result->push_back (make_pair (s("shape"), s("box")));
	return result;
}


/*
 * Labels for graphviz
 */
String*
Entry_block::get_graphviz_label ()
{
	return s("ENTRY");
}

String* Exit_block::get_graphviz_label ()
{
	return s("EXIT");
}

String* Empty_block::get_graphviz_label ()
{
	return s("");
}

String* Branch_block::get_graphviz_label ()
{
	return branch->variable_name->get_ssa_var_name ();
}

String*
Statement_block::get_graphviz_label ()
{
	stringstream ss;
	MIR_unparser mup(ss, true);
	mup.unparse(statement);
	return s(ss.str());
}

list<pair<String*,String*> >*
Branch_block::get_graphviz_properties ()
{
	list<pair<String*,String*> >* result =
		Basic_block::get_graphviz_properties ();

	result->push_back (make_pair (s("shape"), s("diamond")));

	return result;
}


list<pair<String*,list<String*> > >*
Basic_block::get_graphviz_bb_properties ()
{
	list<pair<String*,list<String*> > >* result = new list<pair<String*,list<String*> > >;
//	if (defs)
//		result->push_back (pair<String*, Set*> (s("defs"), defs));
//	if (uses)
//		result->push_back (pair<String*, Set*> (s("uses"), uses));
//	if (aliases && dynamic_cast<Entry_block*> (this))
//		result->push_back (pair<String*, Set*> (s("aliases"), aliases));
	return result;
}

list<pair<String*,list<String*> > >*
Basic_block::get_graphviz_head_properties ()
{
	list<pair<String*,list<String*> > >* result = new list<pair<String*,list<String*> > >;
	// Phi nodes
	foreach (Phi* phi, *get_phi_nodes ())
	{
		list<String*> list;
		Rvalue* arg;
		Edge* edge;
		foreach (tie (arg, edge), *phi->get_arg_edges ())
		{
			stringstream ss;
			ss << "(" << cfg->index[edge->source->vertex] << "): ";
			if (isa<VARIABLE_NAME> (arg))
				ss << *dyc<VARIABLE_NAME> (arg)->get_ssa_var_name ();
			else
				ss << *dyc<Literal> (arg)->get_value_as_string ();

			list.push_back (s (ss.str()));
		}

		result->push_back (make_pair (phi->lhs->get_ssa_var_name (), list));
	}

//	if (live_in)
//		result->push_back (make_pair (s("IN"), live_in));
	return result;
}

list<pair<String*,list<String*> > >*
Basic_block::get_graphviz_tail_properties ()
{
	list<pair<String*,list<String*> > >* result = new list<pair<String*,list<String*> > >;
//	if (live_out)
//		result->push_back (make_pair (s("OUT"), live_out));
	return result;
}

/*
 * SSA
 */

void
Basic_block::add_phi_function (VARIABLE_NAME* var_name)
{
	// We only want 1 phi node per variable name, regardless of the number of
	// versions.
	assert (not has_phi_function (var_name));
	phi_nodes[*var_name->value] = new Phi (var_name->clone ());
}

bool
Basic_block::has_phi_function (VARIABLE_NAME* var_name)
{
	return phi_nodes.has (*var_name->value);
}

List<Phi*>*
Basic_block::get_phi_nodes ()
{
	List<Phi*>* result = new List<Phi*>;

	pair<string, Phi*> pair;
	foreach (pair, phi_nodes)
		result->push_back (pair.second);

	return result;
}

void
Basic_block::set_phi_nodes (Phi_list* new_phis)
{
	// TODO: what does indexing on the old name get us?
	remove_phi_nodes ();
	foreach (Phi* phi, *new_phis)
	{
		phi_nodes[*phi->lhs->value] = phi;
	}
}

/* Merge the phi nodes from OTHER into this BB. */
void
Basic_block::merge_phi_nodes (Basic_block* other)
{
	// TODO: This might add the same entry twice to the args list. We should
	// really be using a set.
	
	// TODO find a test case for this
	assert (get_phi_nodes ()->size () == 0 || other->get_phi_nodes()->size() == 0);
	foreach (Phi* phi, *other->get_phi_nodes ())
	{
		if (has_phi_function (phi->lhs))
		{
			assert (0); // TODO: this doesnt work
			pair<Rvalue*, Edge*> arg;
			foreach (arg, *phi->get_arg_edges ())
				phi_nodes[*phi->lhs->value]->get_arg_edges ()->push_back (arg);
		}
		else
			phi_nodes[*phi->lhs->value] = phi;
	}
}

void
Basic_block::remove_phi_nodes ()
{
	phi_nodes.clear ();
}

/* Replace any phi node with a single argument with an assignment. */
void
Basic_block::fix_solo_phi_args ()
{
	// TODO: The theory is that each Phi node executes simultaneously. If
	// there are dependencies between the nodes, this could be wrong.

	BB_list* replacements = new BB_list ();
	foreach (Phi* phi, *get_phi_nodes ())
	{
		Rvalue_list* args = phi->get_args ();
		if (args->size () == 1)
		{
			replacements->push_back (
				new Statement_block (
					cfg,
					new Assign_var (
						phi->lhs,
						false,
						args->front ())));

			phi_nodes.erase (*phi->lhs->value);
		}
	}

	replacements->push_back (this);
	replace (replacements);
}

void
Basic_block::insert_predecessor (Basic_block* bb)
{
	cfg->insert_predecessor_bb (this, bb);
}

BB_list*
Basic_block::get_predecessors ()
{
	return cfg->get_bb_predecessors (this);
}

BB_list*
Basic_block::get_successors ()
{
	return cfg->get_bb_successors (this);
}

Basic_block*
Basic_block::get_successor ()
{
	BB_list* succs = get_successors ();
	assert (succs->size() == 1);
	return succs->front ();
}

Edge_list*
Basic_block::get_predecessor_edges ()
{
	return cfg->get_edge_predecessors (this);
}

Edge_list*
Basic_block::get_successor_edges ()
{
	return cfg->get_edge_successors (this);
}


Edge*
Basic_block::get_successor_edge ()
{
	Edge_list* succs = get_successor_edges ();
	assert (succs->size() == 1);
	return succs->front ();
}


Basic_block*
Branch_block::get_true_successor ()
{
	Edge_list* succs = get_successor_edges ();
	assert (succs->size() == 2);

	foreach (Edge* succ, *succs)
		if (cfg->is_true_edge (succ))
			return succ->target;

	assert (0);
}


Basic_block*
Branch_block::get_false_successor ()
{
	Edge_list* succs = get_successor_edges ();
	assert (succs->size() == 2);

	foreach (Edge* succ, *succs)
		if (not cfg->is_true_edge (succ))
			return succ->target;

	assert (0);
}

Edge*
Branch_block::get_true_successor_edge ()
{
	Edge_list* succs = get_successor_edges ();
	assert (succs->size() == 2);

	foreach (Edge* succ, *succs)
		if (cfg->is_true_edge (succ))
			return succ;

	assert (0);
}

Edge*
Branch_block::get_false_successor_edge ()
{
	Edge_list* succs = get_successor_edges ();
	assert (succs->size() == 2);

	foreach (Edge* succ, *succs)
		if (not cfg->is_true_edge (succ))
			return succ;

	assert (0);
}

void
Branch_block::switch_successors ()
{
	foreach (Edge* succ, *get_successor_edges ())
		succ->direction = !succ->direction;
}

void
Basic_block::remove ()
{
	cfg->remove_bb (this);
}

void
Basic_block::replace (BB_list* replacements)
{
	cfg->replace_bb (this, replacements);

}

void
Branch_block::set_always (bool direction)
{
	cfg->consistency_check ();

	Edge* true_edge = get_true_successor_edge ();
	Edge* false_edge = get_false_successor_edge ();

	Basic_block* succ = direction ? get_true_successor () : get_false_successor ();

	foreach (Edge* edge, *get_predecessor_edges ())
	{
		edge->replace_target (succ);

		foreach (Phi* phi, *get_phi_nodes ())
			phi->replace_edge (edge, cfg->get_edge (edge->source, succ));
	}

	succ->merge_phi_nodes (this);

	// Fix up phis
	cfg->remove_edge (true_edge);
	cfg->remove_edge (false_edge);
	remove ();

	cfg->consistency_check ();
}

BB_list*
Basic_block::get_dominance_frontier ()
{
	return cfg->dominance->get_bb_dominance_frontier (this);
}

Basic_block*
Basic_block::get_immediate_dominator ()
{
	return cfg->dominance->get_bb_immediate_dominator (this);
}

bool
Basic_block::is_in_dominance_frontier (Basic_block* df)
{
	return cfg->dominance->is_bb_in_dominance_frontier (this, df);
}

bool
Basic_block::is_dominated_by (Basic_block* bb)
{
	return cfg->dominance->is_bb_dominated_by (this, bb);
}

void
Basic_block::add_to_dominance_frontier (Basic_block* bb)
{
	cfg->dominance->add_to_bb_dominance_frontier (this, bb);
}

BB_list*
Basic_block::get_dominated_blocks ()
{
	return cfg->dominance->get_blocks_dominated_by_bb (this);
}

VARIABLE_NAME_list*
Basic_block::get_pre_ssa_defs ()
{
	return cfg->duw->get_bb_defs (this);
}

VARIABLE_NAME_list*
Basic_block::get_pre_ssa_uses ()
{
	return cfg->duw->get_bb_uses (this);
}

int
Basic_block::get_index ()
{
	return cfg->index[vertex];
}


/*
 * Debugging
 */

void
Entry_block::dump()
{
	DEBUG ("Entry block");
}

void
Exit_block::dump()
{
	DEBUG ("Exit block");
}

void
Branch_block::dump()
{
	DEBUG ("Branch block (" << cfg->index[vertex] << ")");
}

void
Statement_block::dump()
{
	CHECK_DEBUG ();

	DEBUG ("Statement block (" << cfg->index[vertex] << ")");
}
void
Empty_block::dump()
{
	DEBUG ("Empty block (" << cfg->index[vertex] << ")");
}
