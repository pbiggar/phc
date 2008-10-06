
#include <boost/foreach.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/dominator_tree.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/transpose_graph.hpp>
#include <boost/graph/reverse_graph.hpp>
#include <boost/graph/topological_sort.hpp>

#include "process_ir/General.h"

#include "SSA.h"
#include "Phi.h"
#include "Def_use.h"
#include "Basic_block.h"

using namespace MIR;
using namespace boost;

// We use Muchnick, Section 8.11 (which is essentially the same as the
// Minimal SSA form from the original Cytron, Ferrante, Rosen, Wegman and
// Zadeck paper), and Cooper/Torczon Chapter 9.

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
	stack<int> st;
	foreach (tie (name,st), var_stacks)
	{
		cdebug << name << ": (TOP) ";
		stack<int> copy (st);
		while (copy.size ())
		{
			cdebug << copy.top () << ", ";
			copy.pop ();
		}
		cdebug << "(BOTTOM)" << endl;
	}
}

void 
SSA_renaming::rename_vars (Basic_block* bb)
{
	DEBUG ("renaming vars in " << *bb->get_graphviz_label ());
	debug_var_stacks ();

	// Convert the phi nodes
	foreach (VARIABLE_NAME* phi_lhs, *bb->get_phi_lhss())
	{
		DEBUG ("converting phi lhs");
		debug (phi_lhs);
//		create_new_ssa_name (phi_lhs);

		VARIABLE_NAME* clone = phi_lhs->clone ();
		create_new_ssa_name (clone);
		bb->update_phi_node (phi_lhs, clone);

		DEBUG (" to ");
		debug (phi_lhs);
	}

	// Rename local variable uses
	foreach (VARIABLE_NAME* use, *bb->get_pre_ssa_uses ())
	{
		DEBUG ("Converting use " << *use->get_ssa_var_name ());
		debug (use);
		use->convert_to_ssa_name (read_var_stack (use));
		DEBUG (" to ");
		debug (use);
	}

	// Create new names for defs
	foreach (VARIABLE_NAME* def, *bb->get_pre_ssa_defs ())
	{
		DEBUG ("Converting def " << *def->get_ssa_var_name ());
		debug (def);
		create_new_ssa_name (def);
		DEBUG (" to ");
		debug (def);
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


SSA_op*
SSA_op::for_bb (Basic_block* bb)
{
	// Fail on Phis

	// TODO:handle formal here?
	if (isa<Branch_block> (bb))
		return new SSA_branch (dyc<Branch_block> (bb));
	else
		return new SSA_stmt (dyc<Statement_block> (bb));
}

SSA_phi::SSA_phi (Basic_block* bb, VARIABLE_NAME* phi_lhs)
: bb (bb)
, phi_lhs (phi_lhs)
{
}

SSA_stmt::SSA_stmt (Statement_block* bb) : bb (bb) {}
SSA_branch::SSA_branch (Branch_block* bb) : bb (bb) {}
SSA_formal::SSA_formal (Entry_block* bb) : bb (bb) {}

Statement* SSA_stmt::get_statement () { return bb->statement; }

Basic_block* SSA_stmt::get_bb () { return bb; }
Basic_block* SSA_formal::get_bb () { return bb; }
Basic_block* SSA_branch::get_bb () { return bb; }
Basic_block* SSA_phi::get_bb () { return bb; }

void SSA_stmt::dump()
{
	DEBUG ("SSA_stmt: ");
	bb->dump ();
}

void SSA_branch::dump()
{
	DEBUG ("SSA_branch: ");
	bb->dump ();
}

void SSA_formal::dump()
{
	DEBUG ("SSA_formal: ");
	bb->dump ();
}

void SSA_phi::dump()
{
	DEBUG ("SSA_phi: " << *phi_lhs->get_ssa_var_name () << ", ");
	bb->dump ();
}


bool ssa_op_ptr_comparison (SSA_op* op1, SSA_op* op2)
{
	// order on types first
	if (typeid (*op1) != typeid (*op2))
		return typeid (*op1).name () < typeid (*op2).name ();


	// Dont compare BB indices, they might be overwritten
	if (isa<SSA_phi> (op1))
	{
		SSA_phi* phi1 = dyc<SSA_phi> (op1);
		SSA_phi* phi2 = dyc<SSA_phi> (op2);
		if (phi1->bb != phi2->bb)
			return phi1->bb->vertex < phi2->bb->vertex;
		else
			// compare variable names
			return *phi1->phi_lhs < *phi2->phi_lhs;
	}
	else
	{
		// Compare vertex pointers, this wont change, even when the
		// graph is updated.
		return op1->get_bb ()->vertex < op2->get_bb ()->vertex;
	}
}

VARIABLE_NAME_list*
SSA_stmt::get_uses ()
{
	return bb->cfg->duw->get_nonphi_uses (bb);
}

VARIABLE_NAME_list*
SSA_phi::get_uses ()
{
	VARIABLE_NAME_list* result = new VARIABLE_NAME_list;
	foreach (Rvalue* use, *bb->get_phi_args (phi_lhs))
		if (isa<VARIABLE_NAME> (use))
			result->push_back (dyc<VARIABLE_NAME> (use));

	return result;
}

VARIABLE_NAME_list*
SSA_branch::get_uses ()
{
	return new VARIABLE_NAME_list (bb->branch->variable_name);
}

VARIABLE_NAME_list*
SSA_formal::get_uses ()
{
	return new VARIABLE_NAME_list ();
}
