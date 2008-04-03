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

#include "Dead_code_elimination.h"
#include "Use_def_counter.h"
#include "process_ir/General.h"
#include "HIR_visitor.h"

using namespace HIR;

Dead_code_elimination::Dead_code_elimination ()
: in_method (false)
{
}

void Dead_code_elimination::pre_method (Method* in, List<Method*>* out)
{
	// each function is separate
	use_counts.clear ();
	def_counts.clear ();

	// count uses and defs
	in->visit (new Use_def_counter (use_counts, def_counts));

	in_method = true;

	out->push_back (in);
}

void Dead_code_elimination::post_method (Method* in, List<Method*>* out)
{
	in_method = false;
	out->push_back (in);
}

void Dead_code_elimination::pre_eval_expr (Eval_expr* in, List<Statement*>* out)
{
	// only method, not the global part
	if (!in_method)
	{
		cdebug << "Ignore non-method" << endl;;
		out->push_back (in);
		return;
	}

	// get useful variables
	VARIABLE_NAME *lhs, *rhs;
	Assignment* assignment;
	if (extract_simple_assignment (in, lhs, rhs, assignment))
	{
		cdebug << "is simple assignment" << endl;
	
		// Remove statement
		if (lhs->attrs->is_true ("phc.codegen.compiler_generated")
			&& use_counts [*lhs->value] == 0
			&& def_counts [*lhs->value] == 1)
		{
			cdebug << "removing statement" << endl;

			// note lack of out->push_back (in);
			iterate_again = true;
			return;
		}
		else
		{
			cdebug << "Not removing: ";
			debug (in);
		}
	}
	out->push_back (in);
}
