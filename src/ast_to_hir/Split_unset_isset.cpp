/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Move isset and unset into individual calls.
 */

#include "Split_unset_isset.h"

using namespace HIR;

/*
 * Convert
 *		unset($x, $y, $z);
 * into
 *		unset($x);
 *		unset($y);
 * 	unset($z);
 */
void Split_unset_isset::pre_eval_expr(Eval_expr * in, List<Statement*>* out)
{
	Expr* unset = new Method_invocation(
		NULL, 	// NULL target
		new METHOD_NAME(new String("unset")),
		NULL	// Arbitrary list of parameters
		);

	if(in->expr->match(unset))
	{
		Method_invocation* inv = dynamic_cast<Method_invocation*>(in->expr);
		assert(inv);

		List<Actual_parameter*>::const_iterator i;
		for(i = inv->actual_parameters->begin();
			i != inv->actual_parameters->end();
			i++)
		{
			assert(!(*i)->is_ref);
			out->push_back(new Eval_expr(new Method_invocation("unset", (*i)->expr)));
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
	if(in->method_name->match(new METHOD_NAME(new String("isset"))))
	{
		List<Expr*>* terms = new List<Expr*>;

		List<Actual_parameter*>::const_iterator i;
		for(i = in->actual_parameters->begin();
			i != in->actual_parameters->end();
			i++)
		{
			assert(!(*i)->is_ref);
			terms->push_back(new Method_invocation("isset", (*i)->expr));
		}

		List<Expr*>::const_iterator j = terms->begin();
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

