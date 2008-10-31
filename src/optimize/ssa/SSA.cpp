#include "process_ir/General.h"
#include "optimize/Basic_block.h"

#include "lib/Stack.h"

#include "SSA.h"
#include "Phi.h"

using namespace MIR;
using namespace boost;

SSA_renaming::SSA_renaming (CFG* cfg)
: cfg(cfg)
, counter (0)
{
}

void
SSA_renaming::push_to_var_stack (VARIABLE_NAME* var_name, int version)
{
	var_stacks[*var_name->value].push (version);
}

int
SSA_renaming::read_var_stack (VARIABLE_NAME* var_name)
{
	// In traditional SSA, all variables are initialized at the start of a
	// function. Not so here (though it could be done that way).
	if (var_stacks[*var_name->value].size () == 0)
		push_to_var_stack (var_name, counter++);

	int result = var_stacks[*var_name->value].top();
	return result;
}

void
SSA_renaming::pop_var_stack (VARIABLE_NAME* var_name)
{
	var_stacks[*var_name->value].pop();
}

void 
SSA_renaming::create_new_ssa_name (VARIABLE_NAME* var_name)
{
	var_name->convert_to_ssa_name (counter);
	push_to_var_stack (var_name, counter++);
}

void
SSA_renaming::debug_var_stacks ()
{
	CHECK_DEBUG ();
	string name;
	Stack<int> st;
	foreach (tie (name,st), var_stacks)
	{
		cdebug << name << ": (TOP) ";
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
	DEBUG ("renaming vars in " << *bb->get_graphviz_label ());
	debug_var_stacks ();

	// Phis, Chis and Mus use indexing, and when we put them in SSA form,
	// their indexing changes. As a result, we need to remove the old one, and
	// add the new one.

	// Convert the phi nodes
	foreach (VARIABLE_NAME* phi_lhs, *bb->get_phi_lhss())
	{
		VARIABLE_NAME* clone = phi_lhs->clone ();
		create_new_ssa_name (clone);
		bb->update_phi_node (phi_lhs, clone);
	}


	// Rename local variable uses
	VARIABLE_NAME_list* uses = bb->get_pre_ssa_uses ();
	uses->push_back_all (bb->get_chi_rhss ());
	foreach (VARIABLE_NAME* use, *uses)
		use->convert_to_ssa_name (read_var_stack (use));

	// Mus are indexed on their var_name
	foreach (VARIABLE_NAME* mu, *bb->get_mus())
	{
		VARIABLE_NAME* clone = mu->clone ();
		clone->convert_to_ssa_name (read_var_stack (clone));
		bb->update_mu_node (mu, clone);
	}


	// Create new names for defs
	foreach (VARIABLE_NAME* def, *bb->get_pre_ssa_defs ())
		create_new_ssa_name (def);

	// Chis are indexed on the lhs
	foreach (VARIABLE_NAME* lhs, *bb->get_chi_lhss ())
	{
		VARIABLE_NAME* clone = lhs->clone ();
		create_new_ssa_name (clone);
		bb->update_chi_lhs (lhs, clone);
	}


	// Copy names to CFG successors (including names defined in
	// predecessor, which are not redefined here).
	foreach (Basic_block* succ, *bb->get_successors ())
		foreach (VARIABLE_NAME* phi_lhs, *succ->get_phi_lhss())
			succ->add_phi_arg (phi_lhs, read_var_stack (phi_lhs), cfg->get_edge (bb, succ));


	// Recurse down the dominator tree
	foreach (Basic_block* dominated, *bb->get_dominated_blocks ())
		rename_vars (dominated);


	// Before going back up the tree, get rid of new variable names from
	// the stack, so the next node up sees its own names.
	foreach (VARIABLE_NAME* def, *bb->get_pre_ssa_defs ())
		pop_var_stack (def);
}


