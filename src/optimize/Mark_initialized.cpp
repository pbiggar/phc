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
#include "Address_taken.h"

using namespace boost;
using namespace MIR;


Mark_initialized::Mark_initialized ()
: Flow_visitor (FORWARD_FLOW)
{
}

void
Mark_initialized::run (CFG* cfg)
{
	aliasing = new Address_taken;
	aliasing->run (cfg);

	Flow_visitor::run (cfg);
}

void
Mark_initialized::init_block (Basic_block* bb)
{
	// all vars automatically UNINIT
	// all block automatically !EXECUTED
	// all solutions automatically !REPEAT
	ins[bb] = new Lattice_map;
	outs[bb] = new Lattice_map;
}

void
Mark_initialized::visit_entry_block (Entry_block* bb)
{
	// Initialize local defs
	foreach (VARIABLE_NAME* def, *bb->get_defs (SSA_FORMAL))
		local_defs[bb].insert (def);

	// We dont deal with a few things, like $x =& $a[$i] will initialize $a.
	// The simplest way to do this is to model all aliases as BOTTOM.
	foreach (VARIABLE_NAME* alias, *aliasing->aliases)
		(*ins[bb])[alias] = BOTTOM;
}

void
Mark_initialized::visit_statement_block (Statement_block* bb)
{
	if (Unset* unset = dynamic_cast<Unset*> (bb->statement))
	{
		// TODO: We should be able to ignore these
		assert (unset->target == NULL);
		assert (unset->array_indices->size () == 0);

		local_undefs[bb].insert (dyc<VARIABLE_NAME> (unset->variable_name));
	}
	else
	{
		foreach (VARIABLE_NAME* def, *bb->get_defs (SSA_STMT))
			local_defs[bb].insert (def);
	}
}

bool
Mark_initialized::solution_has_changed (Basic_block* bb)
{
	return repeat[bb];
}

void
Mark_initialized::transfer_in (Basic_block* bb, BB_list* preds)
{
	DEBUG ("transfer IN for block " << bb->get_index ());
	ins[bb]->clear ();
	VARIABLE_NAME* def;
	Lattice_cell* cell;

	// IN = intersection (P) forall P = preds (OUT))
	foreach (Basic_block* pred, *preds)
		if (executed[pred])
		{
			foreach (tie (def, cell), *outs[pred])
				(*ins[bb])[def] = meet ((*ins[bb])[def], cell);
		}
}

void
Mark_initialized::transfer_out (Basic_block* bb, BB_list* succs)
{
	DEBUG ("transfer OUT for block " << bb->get_index ());
	Lattice_map* old = outs[bb]->clone ();

	// IN
	outs[bb] = ins[bb]->clone ();

	// IN U DEFs
	foreach (VARIABLE_NAME* def, local_defs[bb])
		(*outs[bb])[def] = meet ((*outs[bb])[def], INIT);

	// (IN U DEFs) / UNDEFs
	foreach (VARIABLE_NAME* undef, local_undefs[bb])
		(*outs[bb])[undef] = meet ((*outs[bb])[undef], UNINIT);

	executed[bb] = true;
	repeat[bb] = not old->equals (outs[bb]);
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
		DEBUG ("LOCAL_KILL:");
		local_undefs[bb].dump();

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
	}
}

Init_cell* INIT = new Init_cell;
Init_cell* UNINIT = NULL;

void
Init_cell::dump()
{
	if (this == INIT)
	{
		DEBUG ("INIT");
	}
	else if (this == UNINIT)
	{
		DEBUG ("UNINIT");
	}
	else
		phc_unreachable ();
}

bool
Init_cell::equals (Lattice_cell* other)
{
	return other == this;
}
