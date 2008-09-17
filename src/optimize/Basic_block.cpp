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


list<std::pair<String*,Set*> >*
Basic_block::get_graphviz_bb_properties ()
{
	list<pair<String*,Set*> >* result = new list<std::pair<String*,Set*> >;
	if (defs)
		result->push_back (pair<String*, Set*> (s("defs"), defs));
	if (uses)
		result->push_back (pair<String*, Set*> (s("uses"), uses));
	if (aliases && dynamic_cast<Entry_block*> (this))
		result->push_back (pair<String*, Set*> (s("aliases"), aliases));
	return result;
}

list<std::pair<String*,Set*> >*
Basic_block::get_graphviz_head_properties ()
{
	list<std::pair<String*,Set*> >* result = new list<std::pair<String*,Set*> >;
	// Phi nodes
	foreach (Phi* phi, *get_phi_nodes ())
	{
		Set* set = new Set;
		foreach (VARIABLE_NAME* arg, *phi->get_args ())
			set->insert (arg);

		result->push_back (
			pair<String*, Set*> (phi->lhs->get_ssa_var_name (), set));
	}

	if (live_in)
		result->push_back (pair<String*, Set*> (s("IN"), live_in));
	return result;
}

list<std::pair<String*,Set*> >*
Basic_block::get_graphviz_tail_properties ()
{
	list<std::pair<String*,Set*> >* result = new list<std::pair<String*,Set*> >;
	if (live_out)
		result->push_back (pair<String*, Set*> (s("OUT"), live_out));
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
			pair<VARIABLE_NAME*, Edge*> arg;
			foreach (arg, *phi->args)
				phi_nodes[*phi->lhs->value]->args->push_back (arg);
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
	// TODO: The theory is that each Phi node executes simultaneously. If there
	// are dependencies between the nodes, this could be wrong.

	BB_list* replacements = new BB_list (this);
	foreach (Phi* phi, *get_phi_nodes ())
	{
		VARIABLE_NAME_list* args = phi->get_args ();
		if (args->size () == 1)
		{
			replacements->push_front (
				new Statement_block (
					cfg,
					new Assign_var (
						phi->lhs, 
						args->front ())));

			phi_nodes.erase (*phi->lhs->value);
		}
	}

	replace (replacements);
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
	cfg->replace_bb (this, new BB_list);
}

void
Basic_block::replace (BB_list* replacements)
{
	cfg->replace_bb (this, replacements);

}

void
Branch_block::set_always_true ()
{
	// Avoid assertion failures in remove_edge by not setting this edge until
	// laser.
	Edge* true_edge = get_true_successor_edge ();

	// remove the false edge
	cfg->remove_edge (get_false_successor_edge ());

	// set the true edge to always true
	true_edge->direction = indeterminate;
	
	// remove the branch
	remove ();
}

void
Branch_block::set_always_false ()
{ 
	// Avoid assertion failures in remove_edge by not setting this edge until
	// laser.
	Edge* false_edge = get_false_successor_edge ();

	// remove the false edge
	cfg->remove_edge (get_true_successor_edge ());

	// set the false edge to always true
	false_edge->direction = indeterminate;
	
	// remove the branch
	remove ();
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
	DEBUG ("Branch block" << branch->variable_name->get_ssa_var_name ());

}

void
Statement_block::dump()
{
	DEBUG ("Statemnet block");

	MIR_unparser mup(cdebug, true);
	mup.unparse(statement);
}
void
Empty_block::dump()
{
	DEBUG ("Empty block");
}
