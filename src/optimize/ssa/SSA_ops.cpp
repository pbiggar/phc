
#include "process_ir/General.h"

#include "SSA_ops.h"
#include "optimize/Def_use_web.h"

using namespace MIR;

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

SSA_op::SSA_op (int type_flag)
{
	this->type_flag = type_flag;
}

SSA_stmt::SSA_stmt (Statement_block* bb) : SSA_op (SSA_STMT), bb (bb) {}
SSA_branch::SSA_branch (Branch_block* bb) : SSA_op (SSA_BRANCH), bb (bb) {}
SSA_formal::SSA_formal (Basic_block* bb) : SSA_op (SSA_FORMAL), bb (bb) {}

SSA_phi::SSA_phi (Basic_block* bb, Alias_name phi_lhs)
: SSA_op (SSA_PHI)
, bb (bb)
, phi_lhs (phi_lhs)
{
}

SSA_chi::SSA_chi (Basic_block* bb, Alias_name lhs, Alias_name rhs)
: SSA_op (SSA_CHI)
, bb (bb)
, lhs (lhs)
, rhs (rhs)
{
}

SSA_mu::SSA_mu (Basic_block* bb, Alias_name rhs)
: SSA_op (SSA_CHI)
, bb (bb)
, rhs (rhs)
{
}

Statement* SSA_stmt::get_statement () { return bb->statement; }

Basic_block* SSA_stmt::get_bb () { return bb; }
Basic_block* SSA_formal::get_bb () { return bb; }
Basic_block* SSA_branch::get_bb () { return bb; }
Basic_block* SSA_phi::get_bb () { return bb; }
Basic_block* SSA_chi::get_bb () { return bb; }
Basic_block* SSA_mu::get_bb () { return bb; }

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
	DEBUG ("SSA_phi: " << phi_lhs.str () << ", ");
	bb->dump ();
}

void SSA_chi::dump()
{
	DEBUG ("SSA_chi: " << lhs.str () << " <- " << rhs.str());
	bb->dump ();
}

void SSA_mu::dump()
{
	DEBUG ("SSA_mu: " << rhs.str() << ", ");
	bb->dump ();
}


bool ssa_op_ptr_comparison (SSA_op* op1, SSA_op* op2)
{
	// order on types first
	if (typeid (*op1) != typeid (*op2))
		return typeid (*op1).name () < typeid (*op2).name ();

	// Compare vertex pointers, this wont change, even when the
	// graph is updated.
	if (op1->get_bb ()->vertex != op2->get_bb ()->vertex)
		return op1->get_bb ()->vertex < op2->get_bb ()->vertex;

	// Dont compare BB indices, they might be overwritten
	if (isa<SSA_phi> (op1))
	{
		phc_TODO (); // why var names, and not alias_names?
		// compare variable names
//		return *dyc<SSA_phi> (op1)->phi_lhs < *dyc<SSA_phi> (op2)->phi_lhs;
	}
	else if (isa<SSA_chi> (op1))
	{
		phc_TODO (); // why var names, and not alias_names?
//		if (*dyc<SSA_chi> (op1)->lhs->value == *dyc<SSA_chi> (op2)->lhs->value)
//			return *dyc<SSA_chi> (op1)->rhs < *dyc<SSA_chi> (op2)->rhs;
//		else
//			return *dyc<SSA_chi> (op1)->lhs < *dyc<SSA_chi> (op2)->lhs;
	}
	else if (isa<SSA_mu> (op1))
	{
		phc_TODO (); // why var names, and not alias_names?
//		return *dyc<SSA_mu> (op1)->rhs < *dyc<SSA_mu> (op2)->rhs;
	}
	else if (isa<SSA_formal> (op1))
	{
		// only 1 formal node
		return false;
	}
	else if (isa<SSA_stmt> (op1) || isa<SSA_branch> (op1))
	{
		// They are the same BB.
		return false;
	}
	else
	{
		// we should have more to base this on
		phc_TODO ();
	}
}

old_Alias_name_list*
SSA_stmt::get_uses ()
{
	// Phis are different statements, but mus and chis are properties of the
	// current statement.
	return bb->cfg->duw->old_get_block_uses (bb, SSA_STMT | SSA_MU | SSA_CHI);
}

old_Alias_name_list*
SSA_phi::get_uses ()
{
	old_Alias_name_list* result = new old_Alias_name_list;
	foreach (Alias_name use, *bb->old_get_phi_args (phi_lhs))
		result->push_back (use);

	return result;
}

old_Alias_name_list*
SSA_branch::get_uses ()
{
	return new old_Alias_name_list (v2an (bb, bb->branch->variable_name));
}

old_Alias_name_list*
SSA_formal::get_uses ()
{
	// TODO: return RHS of phi nodes?
	return new old_Alias_name_list();
}

old_Alias_name_list*
SSA_chi::get_uses ()
{
	return new old_Alias_name_list(rhs);
}

old_Alias_name_list*
SSA_mu::get_uses ()
{
	return new old_Alias_name_list (rhs);
}
