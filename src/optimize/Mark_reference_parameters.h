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

#ifndef PHC_MARK_REFERENCE_PARAMETERS
#define PHC_MARK_REFERENCE_PARAMETERS

#include "Visit_once.h"

class Mark_reference_parameters : virtual public GC_obj, public Visit_once
{
	// visit_expr needs to be called manually
	void visit_assign_var (Statement_block* bb, MIR::Assign_var* in);
	void visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in);

	void visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in);
};

#endif
