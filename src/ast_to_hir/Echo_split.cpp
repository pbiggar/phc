/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert echo()es to print()s
 */

#include "Echo_split.h"

using namespace AST;

// Split echos into multiple statements. Normal function calls evaluate all
// their actual parameters at once, and then call the expression with the
// results of the evaluations. Echo, however, only evaluates its next argument
// after printing the result of the previouis argument. Functions with
// side-effects will display this.
//
// Convert
//	  echo f (), f();
//	into
//	  print f();
//	  print f();
//
//	We convert to print simply so the later print transformation is easier.
void Echo_split::pre_eval_expr(Eval_expr* in, Statement_list* out)
{
	Method_invocation* echo = new Method_invocation (
			NULL,	
			new METHOD_NAME ("echo"),
			NULL); // match any list (note this doesnt get populated. Use in STMT get the list.)

	if (not in->expr->match (echo))
	{
		out->push_back (in);
		return;
	};

	Actual_parameter_list* params =
		(dyc <Method_invocation> (in->expr))->actual_parameters;

	foreach (Actual_parameter* ap, *params)
	{
		out->push_back (new Eval_expr (
					new Method_invocation (
						NULL,
						new METHOD_NAME ("print"),
						new Actual_parameter_list (ap))));

	}
}
