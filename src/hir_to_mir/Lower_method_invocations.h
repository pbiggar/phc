/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower the parameters of method invocations, adding a run-time check to
 * determine if the parameter is passed by reference.
 */

#ifndef PHC_LOWER_METHOD_INVOCATIONS_H
#define PHC_LOWER_METHOD_INVOCATIONS_H

#include "HIR_lower_expr.h"
#include "MIR.h"
#include "HIR_to_MIR.h"

class Lower_method_invocations : public HIR::Lower_expr
{
private:
	HIR_to_MIR folder;

public:
	HIR::Expr* pre_method_invocation (HIR::Method_invocation* in);

private:
	HIR::Expr* check_builtin (HIR::FOREIGN* container);
};

#endif // PHC_LOWER_METHOD_INVOCATIONS_H
