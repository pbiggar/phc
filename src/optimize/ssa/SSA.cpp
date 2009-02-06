#include "process_ir/General.h"
#include "lib/Stack.h"

#include "optimize/Basic_block.h"
#include "optimize/wpa/Whole_program.h"
#include "optimize/wpa/Def_use.h"
#include "optimize/Def_use_web.h"

#include "SSA.h"
#include "Phi.h"

using namespace MIR;
using namespace boost;

SSA_renaming::SSA_renaming (Whole_program* wp, CFG* cfg)
: wp(wp)
, cfg(cfg)
, counter (1)
{
}

void
SSA_renaming::push_to_var_stack (Alias_name* name)
{
	assert (name->ssa_version == 0);
	var_stacks[*name].push (counter);
	name->set_version (counter);
	counter++;
}

int
SSA_renaming::read_var_stack (Alias_name* name)
{
	// In traditional SSA, all variables are initialized at the start of a
	// function. Not so here (though it could be done that way).
	
	if (var_stacks[*name].size () == 0)
		push_to_var_stack (name);

	return var_stacks[*name].top();
}

void
SSA_renaming::pop_var_stack (Alias_name* name)
{
	var_stacks[*name].pop();
}

void 
SSA_renaming::create_new_ssa_name (Alias_name* name)
{
	push_to_var_stack (name);
}

void
SSA_renaming::debug_var_stacks ()
{
	CHECK_DEBUG ();
	Alias_name name;
	Stack<int> st;
	foreach (tie (name, st), var_stacks)
	{
		cdebug << name.str() << ": (TOP) ";
		Stack<int> copy (st);
		while (copy.size ())
		{
			cdebug << copy.top () << ", ";
			copy.pop ();
		}
		DEBUG ("(BOTTOM)");
	}
}

void 
SSA_renaming::rename_vars (Basic_block* bb)
{
	// Ordering is important here:
	//		- Phi nodes occur before the function, so 1) args get renamed, then
	//		  2) the lhs (actually, this node's phi args are renamed in the
	//		  precessors).
	//		- 3) The statement itself uses the result of the phi operation
	//		- 4) Mu nodes use the uses
	//		- 5) The statements def occur after the uses
	//		- 6) The chi uses occur after the statement def
	//		- 7) The chi defs occur after the chi uses
	//
	DEBUG ("renaming vars in " << *bb->get_graphviz_label ());
	debug_var_stacks ();

	// TODO: phis
	
	foreach (Alias_name* use, *bb->cfg->duw->get_uses (bb))
		use->set_version (read_var_stack (use));

	foreach (Alias_name* def, *bb->cfg->duw->get_defs (bb))
		create_new_ssa_name (def);

	foreach (Alias_name* may_def, *bb->cfg->duw->get_may_defs (bb))
		create_new_ssa_name (may_def);



	// Phis, Chis and Mus use indexing, and when we put them in SSA form,
	// their indexing changes. As a result, we need to remove the old one, and
	// add the new one.
#if 0
	// 2) Convert the phi nodes
	foreach (Alias_name phi_lhs, *bb->get_phi_lhss())
	{
		Alias_name clone = phi_lhs;
		create_new_ssa_name (clone);
		bb->update_phi_node (phi_lhs, clone);
	}


	// 3) Rename the statement's uses
	foreach (Alias_name use, *bb->get_uses_for_renaming ())
		use.set_version (read_var_stack (use));

	// 4) Mus
	// Mus are indexed on their var_name
	foreach (Alias_name mu, *bb->get_mus())
	{
		Alias_name clone = mu;
		clone.set_version (read_var_stack (clone));
		bb->update_mu_node (mu, clone);
	}


	// 5) Create new names for defs
	foreach (Alias_name def, *bb->get_defs_for_renaming ())
		create_new_ssa_name (def);

	// 6) Rename the chi's uses
	foreach (Alias_name use, *bb->get_chi_rhss ())
		use.set_version (read_var_stack (use));

	// 7) Chis are indexed on the lhs
	foreach (Alias_name lhs, *bb->get_chi_lhss ())
	{
		Alias_name clone = lhs;
		create_new_ssa_name (clone);
		bb->update_chi_lhs (lhs, clone);
	}


	// Copy names to CFG successors (including names defined in
	// predecessor, which are not redefined here).
	foreach (Basic_block* succ, *bb->get_successors ())
		foreach (Alias_name phi_lhs, *succ->get_phi_lhss())
			succ->add_phi_arg (phi_lhs, read_var_stack (phi_lhs), cfg->get_edge (bb, succ));
#endif

	// Recurse down the dominator tree
	foreach (Basic_block* dominated, *bb->get_dominated_blocks ())
		rename_vars (dominated);

#if 0

	// Before going back up the tree, get rid of new variable names from
	// the stack, so the next node up sees its own names.

	// In case of duplicates, pop once for each dup.
	Alias_name_list* defs = new Alias_name_list;
	defs->push_back_all (bb->get_defs_for_renaming ());
	defs->push_back_all (bb->get_phi_lhss ()->to_list ());
	defs->push_back_all (bb->get_chi_lhss ());
	foreach (Alias_name def, *defs)
		pop_var_stack (def);

#endif
}


