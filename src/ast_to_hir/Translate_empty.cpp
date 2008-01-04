/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower calls to empty().
 */

#include "Translate_empty.h"

using namespace AST;

Expr* Translate_empty::pre_method_invocation(Method_invocation* in)
{
	if(in->method_name->match(new METHOD_NAME(new String("empty"))))
	{
		CAST* boolean = new CAST(new String("boolean"));
		Actual_parameter* param = *in->actual_parameters->begin();
		assert(!param->is_ref);
		return new Unary_op(new Cast(boolean, param->expr), "!");
	}
	else
	{
		return in;
	}
}
