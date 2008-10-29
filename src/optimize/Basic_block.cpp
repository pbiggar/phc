#include "process_ir/General.h"
#include "process_mir/MIR_unparser.h"
#include "MIR.h"

#include "Basic_block.h"
#include "Def_use.h"

#include "ssa/Dominance.h"

using namespace std;
using namespace MIR;

/* Constructors */

Basic_block::Basic_block(CFG* cfg)
: cfg(cfg)
, vertex (NULL)
{
	phi_lhss = new VARIABLE_NAME_list;
	mus = new VARIABLE_NAME_list;
	chis = new List<pair<MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*> >;
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

List<pair<String*,String*> >*
Basic_block::get_graphviz_properties ()
{
	List<pair<String*,String*> >* result = new List<pair<String*,String*> >;
	result->push_back (make_pair (s("shape"), s("box")));
	return result;
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

List<pair<String*,String*> >*
Branch_block::get_graphviz_properties ()
{
	List<pair<String*,String*> >* result =
		Basic_block::get_graphviz_properties ();

	result->push_back (make_pair (s("shape"), s("diamond")));

	return result;
}


List<pair<String*,String_list> >*
Basic_block::get_graphviz_bb_properties ()
{
	List<pair<String*,String_list> >* result = new List<pair<String*,String_list> >;
//	if (defs)
//		result->push_back (pair<String*, Set*> (s("defs"), defs));
//	if (uses)
//		result->push_back (pair<String*, Set*> (s("uses"), uses));
//	if (aliases && dynamic_cast<Entry_block*> (this))
//		result->push_back (pair<String*, Set*> (s("aliases"), aliases));
	return result;
}

List<pair<String*,String_list> >*
Basic_block::get_graphviz_head_properties ()
{
	List<pair<String*,String_list> >* result = new List<pair<String*,String_list> >;
	// Phi nodes
	foreach (VARIABLE_NAME* phi_lhs, *get_phi_lhss ())
	{
		String_list list;
		foreach (Edge* edge, *get_predecessor_edges ())
		{
			Rvalue* arg = edge->pm[phi_lhs]; // avoid assertion.

			stringstream ss;
			if (arg)
			{
				if (isa<VARIABLE_NAME> (arg))
					ss << *dyc<VARIABLE_NAME> (arg)->get_ssa_var_name ();
				else
					ss << *dyc<Literal> (arg)->get_value_as_string ();
			}
			else
				ss << "XXX"; // missing value.

			ss << " (" << cfg->index[edge->get_source()->vertex] << ")";
			

			list.push_back (s (ss.str()));
		}

		stringstream name;
		name << "PHI (" << *phi_lhs->get_ssa_var_name () << ")";
		result->push_back (make_pair (s(name.str()), list));
	}

	// XXX HACK: add a line break
	if (mus->size() && result->size())
		result->push_back (make_pair (s(""), *(new String_list)));

	// Add mus:
	foreach (VARIABLE_NAME* mu, *mus)
	{
		stringstream name;
		name << "MU (" << *mu->get_ssa_var_name () << ")";
		result->push_back (
			make_pair (
				s(name.str()), 
				*(new String_list)));
	}

	return result;
}

List<pair<String*,String_list> >*
Basic_block::get_graphviz_tail_properties ()
{
	List<pair<String*,String_list> >* result = new List<pair<String*,String_list> >;

	// Add chis:
	VARIABLE_NAME* lhs;
	VARIABLE_NAME* rhs;
	foreach (tie (lhs, rhs), *chis)
	{
		stringstream name;
		name << "CHI (" << *lhs->get_ssa_var_name () << ")";

		result->push_back (
			make_pair (
				s(name.str ()), 
				*(new String_list (
					rhs->get_ssa_var_name ()))));
	}

	return result;
}


/*
 * SSA
 */

/* Merge the phi nodes from OTHER into this BB. */
void
Basic_block::copy_phi_nodes (Basic_block* other)
{
	// Since a phi is an assignment, and variables can only be assigned to once,
	// OTHER's PHIs cant exist in THIS.
	foreach (VARIABLE_NAME* phi_lhs, *other->get_phi_lhss ())
		assert (!has_phi_node (phi_lhs));

	phi_lhss->push_back_all (other->get_phi_lhss());
}

bool
Basic_block::has_phi_node (VARIABLE_NAME* phi_lhs)
{
	foreach (VARIABLE_NAME* lhs, *phi_lhss)
	{
		// Only operator< is defined, not >= or ==
		if (*lhs < *phi_lhs || *phi_lhs < *lhs)
			continue;

		return true;
	}

	return false;
}

void
Basic_block::add_phi_node (VARIABLE_NAME* phi_lhs)
{
	assert (!has_phi_node (phi_lhs));
	phi_lhss->push_back (phi_lhs->clone ());
}

void
Basic_block::add_mu_node (VARIABLE_NAME* mu)
{
	mus->push_back (mu->clone ());
}

void
Basic_block::add_chi_node (VARIABLE_NAME* chi)
{
	chis->push_back (make_pair (chi->clone (), chi->clone ()));
}

void
Basic_block::add_phi_arg (VARIABLE_NAME* phi_lhs, int version, Edge* edge)
{
//	assert (has_phi_node (phi_lhs));
	// phi_lhs doesnt have to be in SSA, since it will be updated later using
	// update_phi_node, if it is not.
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
	phi_lhss->remove (phi_lhs);
	assert (!has_phi_node (phi_lhs));
}


void
Basic_block::remove_mu_nodes ()
{
	chis->clear ();
}

void
Basic_block::remove_chi_nodes ()
{
	mus->clear ();
}

void
Basic_block::remove_virtual_phis ()
{
	foreach (VARIABLE_NAME* phi_lhs, *phi_lhss)
	{
		if (phi_lhs->is_virtual)
		{
			// TODO: add checks that the args are virtual;
			remove_phi_node (phi_lhs);
		}
		else
		{
			// TODO: add checks that the args are NOT virtuals
		}
	}
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



Rvalue_list*
Basic_block::get_phi_args (MIR::VARIABLE_NAME* phi_lhs)
{
	Rvalue_list* result = new Rvalue_list;

	foreach (Edge* pred, *get_predecessor_edges ())
		result->push_back (get_phi_arg_for_edge (pred, phi_lhs));

	return result;
}

VARIABLE_NAME_list*
Basic_block::get_phi_lhss()
{
	// Return a clone, since we sometimes like to update the list
	// (but dont call ->clone, since we dont want clones of the variables).
	VARIABLE_NAME_list* result = new VARIABLE_NAME_list;
	result->push_back_all (phi_lhss);
	return result;
}

MIR::VARIABLE_NAME_list*
Basic_block::get_chi_lhss ()
{
	VARIABLE_NAME_list* result = new VARIABLE_NAME_list;
	VARIABLE_NAME* lhs;
	VARIABLE_NAME* rhs;
	foreach (tie (lhs, rhs), *chis)
	{
		result->push_back (lhs);
	}
	return result;
}


List<pair<MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*> >*
Basic_block::get_chis ()
{
	return chis;
}


MIR::VARIABLE_NAME_list*
Basic_block::get_chi_rhss ()
{
	VARIABLE_NAME_list* result = new VARIABLE_NAME_list;
	VARIABLE_NAME* lhs;
	VARIABLE_NAME* rhs;
	foreach (tie (lhs, rhs), *chis)
	{
		result->push_back (rhs);
	}
	return result;
}

MIR::VARIABLE_NAME_list*
Basic_block::get_mus()
{
	VARIABLE_NAME_list* result = new VARIABLE_NAME_list;
	result->push_back_all (mus);
	return result;
}

Rvalue*
Basic_block::get_phi_arg_for_edge (Edge* edge, VARIABLE_NAME* phi_lhs)
{
	Rvalue* result = edge->pm[phi_lhs];
	assert (result);
	return result;
}

void
Basic_block::set_phi_arg_for_edge (Edge* edge, VARIABLE_NAME* phi_lhs, Rvalue* arg)
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
Basic_block::get_pre_ssa_defs ()
{
	return cfg->duw->get_real_defs (this);
}

VARIABLE_NAME_list*
Basic_block::get_pre_ssa_uses ()
{
	return cfg->duw->get_real_uses (this);
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
