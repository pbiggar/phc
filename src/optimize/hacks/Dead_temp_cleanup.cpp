/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * The lowering passes introduce a lot of unnecessary copies, which
 * add extra reference counts, resulting in extra copying and poor
 * performance.
 *
 * This removes assignments from simple variables to compiler-generated
 * temporaries, so long as the temporary is never used.
 *
 * HACK TODO: Remove.
 * This is exactly the sort of hacky thing we wanted
 * to remove. This would be much better done with a data-flow
 * framework, but is much easier than cleaning up the passes, which
 * would otherwise be necessary.
 *
 */

#include "Dead_temp_cleanup.h"
#include "Use_def_counter.h"
#include "process_ir/General.h"
#include "HIR_visitor.h"

using namespace HIR;

Dead_temp_cleanup::Dead_temp_cleanup ()
{
}

void Dead_temp_cleanup::children_php_script (PHP_script* in)
{
	in->visit (new Use_def_counter ());

	Transform::children_php_script (in);

	in->visit (new Clear_use_defs);
}

void Dead_temp_cleanup::pre_assign_var (Assign_var* in, Statement_list* out)
{
	// get useful variables
	VARIABLE_NAME *lhs = in->lhs;

	if (!isa<HIR::VARIABLE_NAME> (in->rhs))
	{
		out->push_back (in);
		return;
	}

	VARIABLE_NAME *rhs = dyc<HIR::VARIABLE_NAME> (in->rhs);

	DEBUG ("is simple assignment");
	xdebug (lhs);
	xdebug (rhs);

	// Remove statement
	if (lhs->attrs->is_true ("phc.codegen.compiler_generated")
			&& lhs->attrs->get_integer ("phc.use_defs.use_count")->value() == 0
			&& lhs->attrs->get_integer ("phc.use_defs.def_count")->value() == 1)
	{
		DEBUG ("removing statement");

		// note lack of out->push_back (in);
		iterate_again = true;
		return;
	}
	else
	{
		DEBUG ("Not removing: ");
		debug (in);
	}

	out->push_back (in);
}
