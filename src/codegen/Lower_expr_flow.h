/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower control flow inside expressions (",", "&&", "||", "?:") 
 */

#ifndef PHC_LOWER_EXPR_FLOW_H
#define PHC_LOWER_EXPR_FLOW_H

#include "Lower_expr.h"

class Lower_expr_flow : public Lower_expr 
{
public:
	AST_expr* post_bin_op(AST_bin_op* in);
	AST_expr* post_conditional_expr(AST_conditional_expr* in);
};

#endif // PHC_LOWER_EXPR_FLOW_H
