/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Mark actual parameters to function calls as being by-reference, or not by-reference, if we know this to be the case. We should know in all cases except:
 *		OO (we might know with type-inference)
 *		varaible-function calls
 *		dynamic function definition
 *
 *
 *	This is a simple case of checking the Optimization Oracle, and does not require analysis.
 */

#include "Mark_reference_parameters.h"
#include "Oracle.h"

using namespace MIR;

// visit_expr needs to be called manually
void
Mark_reference_parameters::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	visit_expr (bb, in->rhs);
}

void
Mark_reference_parameters::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	visit_expr (bb, in->expr);
}

void
Mark_reference_parameters::visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in)
{
	// TODO: handle methods and static methods
	if (in->target)
		return;

	if (isa<MIR::Variable_method> (in->method_name))
		return;

	Signature* sig = Oracle::get_signature (dyc<METHOD_NAME> (in->method_name));
	if (sig == NULL)
	{
		phc_missed_opt ("Signature not available", in, "%s");
		return;
	}

	int i = 0;
	foreach (Actual_parameter* ap, *in->actual_parameters)
	{
		if (ap->is_ref || sig->is_param_passed_by_ref (i))
			ap->rvalue->attrs->set_true ("phc.codegen.param_by_ref");
		else
			ap->rvalue->attrs->set_true ("phc.codegen.param_not_by_ref");

		i++;
	}
}

