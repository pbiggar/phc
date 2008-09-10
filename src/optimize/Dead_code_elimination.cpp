#include "Dead_code_elimination.h" // TODO: rename file
#include "process_ir/General.h"
#include "Def_use.h"

using namespace MIR;

bool is_side_effecting (Expr* in)
{
	return (isa<New> (in) || isa<Method_invocation> (in));
}

void
DCE::transform_assign_var (Statement_block* bb, Assign_var* in, BB_list* out)
{
	if (bb->cfg->duw->get_def_use_edges (in->lhs)->size () == 0)
	{
		if (is_side_effecting (in->rhs))
			out->push_back (new Statement_block (bb->cfg, new Eval_expr (in->rhs)));
		else
		{
			DEBUG ("Removing BB (no uses)")
			debug (in);
		}
	}
	else
		out->push_back (bb);
}
