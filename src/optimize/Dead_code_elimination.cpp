#include "Dead_code_elimination.h"
#include "process_ir/General.h"

using namespace MIR;

bool is_side_effecting (Expr* in)
{
	return (isa<New> (in) || isa<Method_invocation> (in));
}

void
Dead_code_elimination::transform_statement_block (Statement_block* bb, list<Basic_block*>* out)
{
	if (not isa<Assign_var> (bb->statement))
	{
		out->push_back (bb);
		return;
	}

	Assign_var* in = dyc<Assign_var> (bb->statement);
		
	if (in->is_ref
		|| bb->live_out->contains (in->lhs->value)
		|| bb->aliases->contains (in->lhs->value)
		)
		out->push_back (bb);
	
	else if (is_side_effecting (in->rhs))
		out->push_back (new Statement_block (new Eval_expr (in->rhs)));

	else
	{
		// leave empty
	}
}
