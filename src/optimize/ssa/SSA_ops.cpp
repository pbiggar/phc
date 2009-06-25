
#include "process_ir/General.h"

#include "SSA_ops.h"
#include "optimize/Def_use_web.h"

using namespace MIR;

SSA_op::SSA_op (Basic_block* bb, Alias_name* name, int type_flag)
: bb (bb)
, name (name)
, type_flag (type_flag)
{
}

SSA_use::SSA_use (Basic_block* bb, Alias_name* name, int type_flag)
: SSA_op (bb, name, type_flag)
{
}

SSA_def::SSA_def (Basic_block* bb, Alias_name* name, int type_flag)
: SSA_op (bb, name, type_flag)
{
}


void SSA_op::dump()
{
	CHECK_DEBUG ();
	cdebug << demangle (this) << " (" << name->str () << ") in BB " << bb->ID << " ";
}

bool ssa_op_ptr_comparison (SSA_op* op1, SSA_op* op2)
{
	// order on types first
	if (typeid (*op1) != typeid (*op2))
		return typeid (*op1).name () < typeid (*op2).name ();

	// Compare vertex pointers, this wont change, even when the
	// graph is updated.
	if (op1->bb->vertex != op2->bb->vertex)
		return op1->bb->vertex < op2->bb->vertex;

	if (op1->type_flag != op2->type_flag)
		return op1->type_flag < op2->type_flag;

	return *op1->name < *op2->name;
}

SSA_use_list*
SSA_def::get_uses ()
{
	return rewrap_list<SSA_use> (&aux_ops);
}

SSA_def_list*
SSA_use::get_defs ()
{
	return rewrap_list<SSA_def> (&aux_ops);
}

