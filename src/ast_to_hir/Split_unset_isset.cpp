/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Move isset and unset into individual calls.
 */

#include "Split_unset_isset.h"

using namespace AST;

/*
 * Convert
 *		unset($x, $y, $z);
 * into
 *		unset($x);
 *		unset($y);
 * 	unset($z);
 */
void Split_unset_isset::pre_eval_expr(Eval_expr * in, Statement_list* out)
{
	Expr* unset = new Method_invocation(
		NULL, 	// NULL target
		new METHOD_NAME(new String("unset")),
		NULL	// Arbitrary list of parameters
		);

	if(in->expr->match(unset))
	{
		Method_invocation* inv = dyc<Method_invocation>(in->expr);

		foreach(Actual_parameter* ap, *inv->actual_parameters)
		{
			assert(!ap->is_ref);
			out->push_back(new Eval_expr(new Method_invocation("unset", ap->expr)));
		}
	}
	else
	{
		out->push_back(in);
	}
}

/*
 * convert
 * 		isset($x, $y, $z)
 * into
 * 		isset($x) && isset($y) && isset($z)
 */
Expr* Split_unset_isset::pre_method_invocation(Method_invocation* in)
{
	if(in->method_name->match(new METHOD_NAME("isset")))
	{
		Expr_list* terms = new Expr_list;

		foreach(Actual_parameter* ap, *in->actual_parameters)
		{
			assert(!ap->is_ref);
			terms->push_back(new Method_invocation("isset", ap->expr));
		}

		Expr_list::const_iterator j = terms->begin();
		Expr* result = *j++;
		for( ; j != terms->end(); j++)
		{
			result = new Bin_op(result, *j, "&&");	
		}

		return result;
	}
	else
	{
		return in;
	}
}

