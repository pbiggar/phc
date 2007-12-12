/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert echo()es to print()s
 */

#include "Echo_split.h"

using namespace HIR;

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
void Echo_split::pre_eval_expr(Eval_expr* in, List<Statement*>* out)
{
	Method_invocation* echo = new Method_invocation (
			NULL,	
			new METHOD_NAME (new String("echo")),
			NULL); // match any list (note this doesnt get populated. Use in STMT get the list.)

	if (not in->expr->match (echo))
	{
		out->push_back (in);
		return;
	};

	List<Actual_parameter*>* params =
		(dynamic_cast <Method_invocation*> (in->expr))->actual_parameters;
	assert (params);

	List<Actual_parameter*>::const_iterator i;
	for (i = params->begin (); i != params->end(); i++)
	{
		out->push_back (new Eval_expr (
					new Method_invocation (
						NULL,
						new METHOD_NAME (new String ("print")),
						new List<Actual_parameter*> (*i))));

	}
}
