/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Do miscellaneous annotations for optimizations - simple cases which involve
 * checking the Optimization Oracle, and do not require analysis.
 *
 
 *
 */

#include "Misc_annotations.h"
#include "Oracle.h"
#include "Def_use_web.h"

using namespace MIR;

// visit_expr needs to be called manually
void
Misc_annotations::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	visit_expr (bb, in->rhs);
}

void
Misc_annotations::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	visit_expr (bb, in->expr);
}

/* Mark actual parameters to function calls as being by-reference, or not
 * by-reference, if we know this to be the case. We should know in all cases
 * except:
 *		OO (we might know with type-inference)
 *		varaible-function calls
 *		dynamic function definition
 */
void
mark_by_ref (Method_invocation* in)
{
	// TODO: handle methods and static methods
	if (in->target)
		return;

	if (isa<MIR::Variable_method> (in->method_name))
		return;

  phc_optimization_exception ("Optimizing by marking known references is not supported");
/*	Signature* sig = Oracle::get_signature (dyc<METHOD_NAME> (in->method_name));
	if (sig == NULL)
	{
		phc_missed_opt ("Signature not available", in, "%s");
		return;
	}

	CTS ("resolve-by-ref");
	int i = 0;
	foreach (Actual_parameter* ap, *in->actual_parameters)
	{
		if (ap->is_ref || sig->is_param_passed_by_ref (i))
			ap->rvalue->attrs->set_true ("phc.optimize.param_by_ref");
		else
			ap->rvalue->attrs->set_true ("phc.optimize.param_not_by_ref");

		i++;
	}
	*/
}

void
mark_zend_reference_bug (Method_invocation* in)
{
	// Mark the special case of the function returning by reference and the
	// called function being a ZEND_FUNCTION_CALL.
	if (in->target)
		return;

	if (isa<MIR::Variable_method> (in->method_name))
		return;

  phc_optimization_exception ("Optimizing by marking the zend reference bug is not supported");
/*
	// Any function for which we have a signature is a ZEND_FUNCTION_CALL
	Signature* sig = Oracle::get_signature (dyc<METHOD_NAME> (in->method_name));
	if (sig == NULL)
		return;


	CTS ("resolve-return-by-ref");
	if (sig->return_by_ref)
		in->attrs->set_true ("phc.optimize.return_reference_bug");
	else
		in->attrs->set_true ("phc.optimize.no_return_reference_bug");
*/

}

void
Misc_annotations::visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in)
{
	mark_by_ref (in);
	mark_zend_reference_bug (in);
}

/*
 * Mark variables which cannot be references
 */
void
Misc_annotations::annotate_non_by_ref_vars (Basic_block* bb)
{
//	Alias_name_list* names = new Alias_name_list;
  phc_optimization_exception ("Optimizing by annotating the non-reference variables is not supported");
//	names->push_back_all (bb->cfg->duw->get_block_defs (bb));
//	names->push_back_all (bb->cfg->duw->get_block_uses (bb));
//	foreach (Alias_name* name, *names)
//	{
/*
		phc_TODO ();
		if (!aliasing->aliases->has (var))
		{
			CTS ("resolve-non-ref");
			var->attrs->set_true ("phc.optimize.cannot_be_ref");
		}*/
//	}
}

void
Misc_annotations::visit_basic_block (Basic_block* bb)
{
	annotate_non_by_ref_vars (bb);
}
