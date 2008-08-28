#include "Dead_code_elimination.h"
#include "process_ir/General.h"

using namespace MIR;

bool is_side_effecting (Expr* in)
{
	return (isa<New> (in) || isa<Method_invocation> (in));
}

void
Dead_code_elimination::transform_assign_var (Statement_block* bb, Assign_var* in, list<Basic_block*>* out)
{
	if (in->is_ref
		|| bb->live_out->has (in->lhs)
		|| bb->aliases->has (in->lhs)
		)
		out->push_back (bb);
	
	else if (is_side_effecting (in->rhs))
		out->push_back (new Statement_block (bb->cfg, new Eval_expr (in->rhs)));

	else
	{
		// leave empty
		DEBUG ("Not removing: ");
		debug (in);
	}
}
