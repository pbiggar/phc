/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * The lowering passes introduce a lot of unnecessary copies, which
 * add extra reference counts, resulting in extra copying and poor
 * performance.
 *
 * HACK TODO: Remove.
 * This is exactly the sort of hacky thing we wanted
 * to remove. This would be much better done with a data-flow
 * framework, but is much easier than cleaning up the passes, which
 * would otherwise be necessary.
 *
 * Since we do not have proper data-flow, we are going to be very
 * conservative, using the following assumptions:
 *
 *	-	Only do this for compiler generated temporaries, this is not
 *		for optimization of user-code, just as a clean-up.
 *
 * -	Simple example: :
 *		1.)	$L1 = $R1; // replaceable
 *		2.)	$L2 = $L1; // removable
 *		becomes:
 *		1.)	$L2 = $R1; // replaced
 *
 *	-	This is not the same as:
 *		1.)	$L1 = $R1;
 *		2.)	$L2 = $L1;	
 *		becoming:
 *		2.)	$L2 = $R1; // $R1 might have been assigned to in-between
 *			
 *	-	$L1 must be a simple variable, and must be annotated with
 *		phc.codegen.compiler_generated
 *
 *	-	Statement 1. must occur after statement 2.
 *
 *	-	Strange cases which break it, shouldn't happen because we only
 *		use this for the restricted set of compiler-generated
 *		temporaries.
 *
 *	The following restrictions may be temporary:
 *
 *	-	Both the assignments involved must be of the form
 *			$R = $L
 *		and must not be by reference, or involve array_indices.
 *	-	$L1 must be assigned exactly once.
 *	-	$L1 must be used exactly once - in the assignment to $L2.
 *	-	$L2 is assigned exactly once, by $R1
 */

#include "Copy_propagation.h"
#include "Use_def_counter.h"
#include "process_ir/General.h"
#include "HIR_visitor.h"

using namespace HIR;

Copy_propagation::Copy_propagation ()
{
}

void Copy_propagation::children_php_script (PHP_script* in)
{
	// count uses and defs
	in->visit (new Use_def_counter);

	Transform::children_php_script (in);

	in->visit (new Clear_use_defs);
}

void Copy_propagation::pre_assign_var (Assign_var* in, Statement_list* out)
{
	xdebug (in);
	debug (in);
	if (!isa<HIR::VARIABLE_NAME> (in->rhs))
	{
		out->push_back (in);
		return;
	}

	VARIABLE_NAME* lhs = in->lhs;
	VARIABLE_NAME* rhs = dyc<VARIABLE_NAME> (in->rhs);

	xadebug (lhs);
	xadebug (rhs);
	DEBUG ("is simple assignment");
	string slhs = *lhs->value;
	string srhs = *rhs->value;

	// add to the list of for future consideration
	if (lhs->attrs->is_true ("phc.codegen.compiler_generated"))
	{
		DEBUG ("lhs is compiler generated");
		replaceable [slhs] = in;
	}

	// consider for immediate removal
	if (replaceable.has (srhs)
			&&	rhs->attrs->get_integer ("phc.use_defs.use_count")->value () == 1
			&&	rhs->attrs->get_integer ("phc.use_defs.def_count")->value () == 1)
	{
		CTS ("copy propagated");
		DEBUG ("rhs is replacable");
		replaceable [srhs]->lhs = lhs->clone ();

		// note lack of out->push_back (in);
		iterate_again = true;
		return;
	}

	out->push_back (in);
}
