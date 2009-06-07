/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Mark variables as definitely initialized, or definitely uninitialized, or
 * maybe initialized.
 *
 *	The flaw in the SCCP algorithm is that we have no information available
 *	when we are defining  a variable. We need to know IN for a variable being
 *	defined in a block. But there is no edge between the def of x0 and the def
 *	of x1. So at the start of the block in which x1 is being defined, where
 *	are we going to the get value for x?
 *
 *
 * The local solution is simple:
 *		DEFS = any definitions in the block (use def-use)
 *		UNDEFS = an unset
 *
 * The transfer solutions are also simple:
 *		IN = intersection (P) forall P = preds (OUT))
 *		OUT = IN U DEF (BB) / UNDEF (BB)
 *		IN(entry) => all variable are UNINIT
 *
 *	We also use an executed bit (taken from CCP by Wegbreit(?)), so that
 *	UNINIT does not have to double as TOP.  If the basic_block's execution bit
 *	is not set, its value is ignored for the merge. Otherwise:
 *		UNINIT intersection INIT = BOTTOM
 *
 * Since the purpose of this pass is to annotate the codegen, we skirt the
 * issue of variable-variables. If there is a variable-variable, then all
 * variables will be in the symbol-table, and this information will come to
 * nothing.
 */

#include "MIR.h"

#include "Mark_initialized.h"
#include "Def_use_web.h"

using namespace boost;
using namespace std;
using namespace MIR;
#if 0

Mark_initialized::Mark_initialized ()
: Flow_visitor (FORWARD_FLOW)
{
}

void
Mark_initialized::init_block (Basic_block* bb)
{
	// all vars automatically UNINIT
	// all block automatically !EXECUTED
	// all solutions automatically !REPEAT
	ins[bb] = new SSA_map ();
	outs[bb] = new SSA_map (UNINIT);
}

void
Mark_initialized::visit_entry_block (Entry_block* bb)
{
	// Initialize local defs
	foreach (Alias_name* def, *bb->cfg->duw->get_defs (bb))
		local_defs[bb].insert (*def);

	// We dont deal with a few things, like $x =& $a[$i] will initialize $a.
	// The simplest way to do this is to model all aliases as BOTTOM.
	// TODO: I'm not sure this is useful at all. Better to model $x[$i] directly
//	foreach (VARIABLE_NAME* alias, *aliasing->aliases)
//		(*ins[bb])[alias] = BOTTOM;
}

void
Mark_initialized::visit_statement_block (Statement_block* bb)
{
	Unset* unset = dynamic_cast<Unset*> (bb->statement);
	if (unset
		&& unset->target == NULL
		&& unset->array_indices->size () == 0)
	{
		phc_TODO ();
//		local_undefs[bb].insert (
//			Alias_name (ST (bb), *dyc<VARIABLE_NAME> (unset->variable_name)->value));
	}
	else
	{
		phc_TODO ();
//		foreach (Alias_name def, *bb->cfg->duw->get_defs (bb)) // TODO need flags?
//			local_defs[bb].insert (def);

	// I think this will be simpler once the use-def settles down.
	phc_TODO ();
/*
		// TODO: we're replicating a lot of def-use information here. But in
		// the def-use, these are may-defs, which doesnt tell us very much.
		// Also, the may-use is only provided in SSA, and doing this analysis
		// in SSA requires changing the indexing of the lattices to use
		// strings.

		// Assign_array doesnt necessarily have a def, but it does initialize
		// the array, if it is not initialized already. While its not a def, we
		// can model it is a such. Note that we can't use may-defs for this.
		if (Assign_array* aa = dynamic_cast<Assign_array*> (bb->statement))
		  local_defs[bb].insert (aa->lhs);
		else if (Assign_next* an = dynamic_cast<Assign_next*> (bb->statement))
		  local_defs[bb].insert (an->lhs);
		else if (Assign_var* av = dynamic_cast<Assign_var*> (bb->statement))
		{
			if (av->is_ref)
			{
				if (Array_access* aa = dynamic_cast<Array_access*> (av->rhs))
					local_defs[bb].insert (aa->variable_name);
				else if (Array_next* an = dynamic_cast<Array_next*> (av->rhs))
					local_defs[bb].insert (an->variable_name);
			}
		}
		*/
	}
	
	DEBUG ("in BB " << bb->get_index ());
	DEBUG ("defs: ");
	local_defs[bb].dump ();
	DEBUG ("undefs: ");
	local_undefs[bb].dump ();
}

bool
Mark_initialized::solution_has_changed (Basic_block* bb)
{
	return repeat[bb];
}

void
Mark_initialized::transfer_in (Basic_block* bb, BB_list* preds)
{
	phc_TODO ();
	/*
	DEBUG ("transfer IN for block " << bb->get_index ());
	ins[bb]->clear ();
	VARIABLE_NAME* var;
	Lattice_cell* cell;
	VARIABLE_NAME_list* vars = new VARIABLE_NAME_list;

	// Get a list of all definitions first. Otherwise, predecessors with
	// UNINIT by default (because the variable isnt mentioned) will meet with
	// TOP and not change if its not mentioned in the predecessor (or if we use
	// UNINIT as the default, then it will meet and go to BOTTOM).
	foreach (Basic_block* pred, *preds)
	{
		if (executed[pred])
		{
			foreach (tie (var, cell), *outs[pred])
				vars->push_back (var);
		}
	}

	// IN = intersection (P) forall P = preds (OUT))
	foreach (var, *vars)
	{
		foreach (Basic_block* pred, *preds)
			if (executed[pred])
				(*ins[bb])[var] = meet ((*ins[bb])[var], (*outs[pred])[var]);
	}

	ins[bb]->dump ();
	*/
}

void
Mark_initialized::transfer_out (Basic_block* bb, BB_list* succs)
{
	phc_TODO ();
	/*
	DEBUG ("transfer OUT for block " << bb->get_index ());
	SSA_map* old = outs[bb]->clone ();

	// IN
	outs[bb] = ins[bb]->clone ();
	outs[bb]->default_value = UNINIT; // dont inherit INs default

	// IN U DEFs
	foreach (VARIABLE_NAME* def, local_defs[bb])
		(*outs[bb])[def] = INIT;

	// (IN U DEFs) / UNDEFs
	foreach (VARIABLE_NAME* undef, local_undefs[bb])
		(*outs[bb])[undef] = UNINIT;

	executed[bb] = true;
	repeat[bb] = not old->equals (outs[bb]);

	outs[bb]->dump ();
	*/
}

void
Mark_initialized::post_pass (CFG* cfg)
{
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		DEBUG ("Basic block " << bb->get_index () << ":");
		DEBUG ("IN:");
		ins[bb]->dump ();
		DEBUG ("OUT:");
		outs[bb]->dump ();
		DEBUG ("LOCAL_DEF:");
		local_defs[bb].dump();
		DEBUG ("LOCAL_UNDEF:");
		local_undefs[bb].dump();

	}
	phc_TODO ();
	/*

	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		ins[bb]->default_value = UNINIT;

		VARIABLE_NAME_list* var_list = new VARIABLE_NAME_list;
		var_list->push_back_all (bb->get_defs (SSA_STMT | SSA_FORMAL));
		var_list->push_back_all (bb->get_uses (SSA_STMT | SSA_BRANCH));
		foreach (VARIABLE_NAME* var, *var_list)
		{
			if ((*ins[bb])[var] == UNINIT)
			{
				var->attrs->set_true ("phc.optimize.is_uninitialized");
				DEBUG (*var->get_ssa_var_name () << " is UNINIT at " << bb->get_index ());
			}
			else if ((*ins[bb])[var] == INIT)
			{
				var->attrs->set_true ("phc.optimize.is_initialized");
				DEBUG (*var->get_ssa_var_name () << " is INIT at " << bb->get_index ());
			}
		}
	}*/
}

Init_cell* INIT = new Init_cell;
Init_cell* UNINIT = new Init_cell;

void
Init_cell::dump(std::ostream& os)
{
	if (this == INIT)
	{
		os << "INIT" << endl;
	}
	else if (this == UNINIT)
	{
		os << "UNINIT" << endl;
	}
	else
		phc_unreachable ();
}

bool
Init_cell::equals (Lattice_cell* other)
{
	return other == this;
}

#endif
