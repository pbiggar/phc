#include "Dead_code_elimination.h" // TODO: rename file
#include "process_ir/General.h"
#include "Def_use.h"
#include "assert.h"
#include "embed/embed.h"

using namespace MIR;

bool is_pure (Expr* in)
{
	Wildcard<METHOD_NAME>* name = new Wildcard<METHOD_NAME>;
	if (in->match (new Method_invocation (NULL, name, NULL))
		&& PHP::is_pure_function (name->value))
		return true;

	return (not (isa<New> (in) || isa<Method_invocation> (in)));
}

void
DCE::transform_assign_var (Statement_block* bb, Assign_var* in, BB_list* out)
{
	if (bb->cfg->duw->get_var_uses(in->lhs)->size () == 0)
	{
		if (not is_pure (in->rhs))
		{
			out->push_back (new Statement_block (bb->cfg, new Eval_expr (in->rhs)));
		}
		else
		{
			DEBUG ("Removing BB (no uses)")
			debug (in);
		}
	}
	else
		out->push_back (bb);
}

// TODO: replace with ADCE
// TODO: add remove SSA_pre_ops

void
DCE::transform_phi_node (Basic_block* bb, VARIABLE_NAME* phi_lhs)
{
	// remove phis with unused LHSs
	if (bb->cfg->duw->get_var_uses (phi_lhs)->size () == 0)
		bb->remove_phi_node (phi_lhs);
}

void
DCE::transform_eval_expr (Statement_block* bb, MIR::Eval_expr* in, BB_list* out)
{
	if (not is_pure (in->expr))
	{
		out->push_back (bb);
	}
}
