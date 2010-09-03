
#include "process_ir/General.h"

#include "SSA_ops.h"
#include "optimize/Def_use_web.h"

using namespace MIR;

SSA_op::SSA_op (Basic_block* bb, SSA_name* name, int type_flag)
: bb (bb)
, name (name)
, type_flag (type_flag)
{
}

SSA_use::SSA_use (Basic_block* bb, SSA_name* name, int type_flag)
: SSA_op (bb, name, type_flag)
{
}

SSA_def::SSA_def (Basic_block* bb, SSA_name* name, int type_flag)
: SSA_op (bb, name, type_flag)
{
}


void SSA_op::dump ()
{
	CHECK_DEBUG ();
	cdebug << demangle (this) << " (" << name->str () << ") in BB " << bb->ID << " ";
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

