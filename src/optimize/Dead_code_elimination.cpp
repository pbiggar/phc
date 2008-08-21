#include "Dead_code_elimination.h"
#include "process_ir/General.h"
#include "cmdline.h"

extern struct gengetopt_args_info args_info;

Dead_code_elimination::Dead_code_elimination () 
{
	this->name = s("DCE");
	this->description = s("Dead-code elimination");
}

bool
Dead_code_elimination::pass_is_enabled (Pass_manager* pm)
{
	return args_info.optimize_given;
}

void
Dead_code_elimination::run (IR::PHP_script* ir_script, Pass_manager* pm)
{
	assert (0);
}

using namespace MIR;

bool is_side_effecting (Expr* in)
{
	return (isa<New> (in) || isa<Method_invocation> (in));
}

void
Dead_code_elimination::transform_assign_var (Statement_block* bb, MIR::Assign_var* in, list<Basic_block*>* out)
{
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

void
Dead_code_elimination::transform_global (Statement_block* bb, MIR::Global* in, list<Basic_block*>* out)
{
	// If the global is not used, remove it. Ignore aliasing effects, since
	// this doesnt affect the contents of a variable, just its scope.
	if (not isa<VARIABLE_NAME> (in->variable_name)
		|| bb->live_out->contains (dyc<VARIABLE_NAME> (in->variable_name)->value))
		out->push_back (bb);
}
