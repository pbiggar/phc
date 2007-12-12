/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower control flow inside expressions (",", "&&", "||", "?:") 
 */

#ifndef PHC_LOWER_EXPR_FLOW_H
#define PHC_LOWER_EXPR_FLOW_H

#include "HIR_lower_expr.h"

class Lower_expr_flow : public Lower_expr 
{
public:
	HIR::Expr* post_bin_op(HIR::Bin_op* in);
	HIR::Expr* post_conditional_expr(HIR::Conditional_expr* in);
};

#endif // PHC_LOWER_EXPR_FLOW_H
