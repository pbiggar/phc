#include "process_ir/General.h"
#include "process_mir/MIR_unparser.h"
#include "MIR.h"

#include "Basic_block.h"
#include "Def_use.h"

#include "ssa/Dominance.h"

using namespace std;
using namespace MIR;
using namespace boost;

/* Constructors */

Basic_block::Basic_block(CFG* cfg)
: cfg(cfg)
, vertex (NULL)
{
	phi_lhss = new Set;
	mus = new Set;
	chis = new Var_map<MIR::VARIABLE_NAME*>;
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

/*
 * Labels for graphviz
 */
String*
Entry_block::get_graphviz_label ()
{
	stringstream ss;
	ss << "ENTRY: (";

	foreach (Formal_parameter* param, *method->signature->formal_parameters)
		ss << *param->var->variable_name->get_ssa_var_name () << ", ";
	
	ss << ")";

	return s (ss.str ());
}

String* Exit_block::get_graphviz_label ()
{
	stringstream ss;
	ss << "EXIT: (";

	// TODO: thats the wrong version!! Is it only a printing problem?
	foreach (Formal_parameter* param, *method->signature->formal_parameters)
		ss << *param->var->variable_name->get_ssa_var_name () << ", ";
	
	ss << ")";

	return s (ss.str ());
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

/*
 * SSA
 */

/* Merge the phi nodes from OTHER into this BB. */
void
Basic_block::copy_phi_nodes (Basic_block* other)
{
	// Since a phi is an assignment, and variables can only be assigned to
	// once, OTHER's PHIs cant exist in THIS.
	foreach (VARIABLE_NAME* phi_lhs, *other->get_phi_lhss ())
		assert (!has_phi_node (phi_lhs));

	phi_lhss = phi_lhss->set_union (other->get_phi_lhss());
}

bool
Basic_block::has_phi_node (VARIABLE_NAME* phi_lhs)
{
	return phi_lhss->has (phi_lhs);
}

void
Basic_block::add_phi_node (VARIABLE_NAME* phi_lhs)
{
	assert (!has_phi_node (phi_lhs));
	phi_lhss->insert (phi_lhs->clone ());
	assert (has_phi_node (phi_lhs));
}

void
Basic_block::add_mu_node (VARIABLE_NAME* mu)
{
	// Same as add_chi_node RE duplicates.
	if (mus->has (mu))
		assert (mu->in_ssa == false);

	mus->insert (mu->clone ());
	assert (mus->has (mu));
}

void
Basic_block::add_chi_node (VARIABLE_NAME* lhs, VARIABLE_NAME* rhs)
{
	// Its OK for this to be here already, say, if there are two uses of the
	// same variable which have the same alias set. It doesnt matter that
	// there is only 1 chi for it.
	if (chis->has (lhs))
		assert (lhs->in_ssa == false);

	// TODO: this doesnt need to be a clone
	// TODO: The callers dont need to clone then
	(*chis)[lhs->clone ()] = rhs->clone ();
	assert (chis->has (lhs));
}

void
Basic_block::add_phi_arg (VARIABLE_NAME* phi_lhs, int version, Edge* edge)
{
	// phi_lhs doesnt have to be in SSA, since it will be updated later using
	// update_phi_node, if it is not.
	//	assert (has_phi_node (phi_lhs));

	VARIABLE_NAME* arg = phi_lhs->clone ();
	arg->set_version (version);
	set_phi_arg_for_edge (edge, phi_lhs, arg);
}

void
Basic_block::remove_phi_nodes ()
{
	foreach (Edge* pred, *get_predecessor_edges ())
		pred->pm.clear ();

	phi_lhss->clear ();
}

void
Basic_block::remove_phi_node (VARIABLE_NAME* phi_lhs)
{
	assert (has_phi_node (phi_lhs));
	foreach (Edge* pred, *get_predecessor_edges ())
		pred->pm.erase (phi_lhs);

	// TODO: are we trying to remove the pointer, when we have a different
	// pointer to the same thing?
	phi_lhss->erase (phi_lhs);
	assert (!has_phi_node (phi_lhs));
}


VARIABLE_NAME*
Basic_block::get_chi_rhs (MIR::VARIABLE_NAME* lhs)
{
	assert (chis->has (lhs));
	return (*chis)[lhs];
}


void
Basic_block::
remove_chi (MIR::VARIABLE_NAME* lhs, MIR::VARIABLE_NAME* rhs)
{
	assert (chis->has (lhs));
	chis->erase (lhs);
	assert (!chis->has (lhs));
}

void
Basic_block::remove_mu (MIR::VARIABLE_NAME* rhs)
{
	assert (mus->has (rhs));
	mus->erase (rhs);
	assert (!mus->has (rhs));
}

void
Basic_block::remove_mu_nodes ()
{
	mus->clear ();
}

void
Basic_block::remove_chi_nodes ()
{
	chis->clear ();
}

void
Basic_block::update_phi_node (MIR::VARIABLE_NAME* old_phi_lhs, MIR::VARIABLE_NAME* new_phi_lhs)
{
	// If a phi_lhs changes into SSA form, its indexing will change. So we must
	// re-insert its args with the new index.
	assert (!old_phi_lhs->in_ssa);
	assert (new_phi_lhs->in_ssa);
	assert (*old_phi_lhs->value == *new_phi_lhs->value);
	add_phi_node (new_phi_lhs);

	foreach (Edge* pred, *get_predecessor_edges ())
	{
		// Not all nodes have their phi argument added yet
		if (pred->pm.has (old_phi_lhs))
			set_phi_arg_for_edge (
					pred,
					new_phi_lhs,
					get_phi_arg_for_edge (pred, old_phi_lhs));
	}

	remove_phi_node (old_phi_lhs);
}

void
Basic_block::update_chi_lhs (MIR::VARIABLE_NAME* old_chi_lhs, MIR::VARIABLE_NAME* new_chi_lhs)
{
	assert (!old_chi_lhs->in_ssa);
	assert (new_chi_lhs->in_ssa);
	assert (*old_chi_lhs->value == *new_chi_lhs->value);

	assert (chis->has (old_chi_lhs));
	assert (!chis->has (new_chi_lhs));

	VARIABLE_NAME* rhs = get_chi_rhs (old_chi_lhs);
	remove_chi (old_chi_lhs, rhs);
	add_chi_node (new_chi_lhs, rhs);

	assert (!chis->has (old_chi_lhs));
	assert (chis->has (new_chi_lhs));
}

void
Basic_block::update_mu_node (MIR::VARIABLE_NAME* old_mu, MIR::VARIABLE_NAME* new_mu)
{
	assert (!old_mu->in_ssa);
	assert (new_mu->in_ssa);
	assert (*old_mu->value == *new_mu->value);

	assert (mus->has (old_mu));
	assert (!mus->has (new_mu));

	remove_mu (old_mu);
	add_mu_node (new_mu);

	assert (!mus->has (old_mu));
	assert (mus->has (new_mu));
}





VARIABLE_NAME_list*
Basic_block::get_phi_args (MIR::VARIABLE_NAME* phi_lhs)
{
	VARIABLE_NAME_list* result = new VARIABLE_NAME_list;

	foreach (Edge* pred, *get_predecessor_edges ())
		result->push_back (get_phi_arg_for_edge (pred, phi_lhs));

	return result;
}

Set*
Basic_block::get_phi_lhss()
{
	// Return a clone, since we sometimes like to update the list
	// (but dont call ->clone, since we dont want clones of the variables).
	return phi_lhss->set_union (new Set);
}

MIR::VARIABLE_NAME_list*
Basic_block::get_chi_lhss ()
{
	VARIABLE_NAME_list* result = new VARIABLE_NAME_list;

	VARIABLE_NAME *lhs, *rhs;
	foreach (tie (lhs, rhs), *chis)
		result->push_back (lhs);

	return result;
}

MIR::VARIABLE_NAME_list*
Basic_block::get_chi_rhss ()
{
	VARIABLE_NAME_list* result = new VARIABLE_NAME_list;

	VARIABLE_NAME *lhs, *rhs;
	foreach (tie (lhs, rhs), *chis)
		result->push_back (rhs);

	return result;
}


Var_map<VARIABLE_NAME*>*
Basic_block::get_chis ()
{
	return chis;
}



Set*
Basic_block::get_mus()
{
	return mus->set_union (new Set);
}

VARIABLE_NAME*
Basic_block::get_phi_arg_for_edge (Edge* edge, VARIABLE_NAME* phi_lhs)
{
	VARIABLE_NAME* result = edge->pm[phi_lhs];
	assert (result);
	return result;
}

void
Basic_block::set_phi_arg_for_edge (Edge* edge, VARIABLE_NAME* phi_lhs, VARIABLE_NAME* arg)
{
	assert (arg);
	edge->pm[phi_lhs] = arg->clone ();
}



/*
 * Block manipulation
 */

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
			return succ->get_target ();

	assert (0);
}


Basic_block*
Branch_block::get_false_successor ()
{
	Edge_list* succs = get_successor_edges ();
	assert (succs->size() == 2);

	foreach (Edge* succ, *succs)
		if (not cfg->is_true_edge (succ))
			return succ->get_target ();

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
	{
		assert (!indeterminate (succ->direction));
		succ->direction = !succ->direction;
	}
}

/*
 * Dominance
 */

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
Basic_block::is_dominated_by (Basic_block* bb)
{
	return cfg->dominance->is_bb_dominated_by (this, bb);
}

BB_list*
Basic_block::get_dominated_blocks ()
{
	return cfg->dominance->get_blocks_dominated_by_bb (this);
}


/*
 * Reverse Dominance
 */
Basic_block*
Basic_block::get_immediate_reverse_dominator ()
{
	return cfg->dominance->reverse_dominance->get_bb_immediate_dominator (this);
}

BB_list*
Basic_block::get_reverse_dominated_blocks ()
{
	return cfg->dominance->reverse_dominance->get_blocks_dominated_by_bb (this);
}

bool
Basic_block::is_reverse_dominated_by (Basic_block* bb)
{
	return cfg->dominance->reverse_dominance->is_bb_dominated_by (this, bb);
}

BB_list*
Basic_block::get_reverse_dominance_frontier ()
{
	return cfg->dominance->reverse_dominance->get_bb_dominance_frontier (this);
}


VARIABLE_NAME_list*
Basic_block::get_defs (int flags)
{
	return cfg->duw->get_block_defs (this, flags);
}

VARIABLE_NAME_list*
Basic_block::get_uses (int flags)
{
	return cfg->duw->get_block_uses (this, flags);
}


VARIABLE_NAME_list*
Basic_block::get_defs_for_renaming ()
{
	return get_defs (SSA_STMT | SSA_FORMAL);
}

VARIABLE_NAME_list*
Basic_block::get_uses_for_renaming ()
{
	return get_uses (SSA_STMT | SSA_BRANCH);
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
	DEBUG ("Branch block (" << get_index() << ")");
}

void
Statement_block::dump()
{
	DEBUG ("Statement block (" << get_index () << ")");
}
void
Empty_block::dump()
{
	DEBUG ("Empty block (" << get_index () << ")");
}
