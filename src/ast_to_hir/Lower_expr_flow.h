/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower control flow inside expressions (",", "&&", "||", "?:") 
 */

#ifndef PHC_LOWER_EXPR_FLOW_H
#define PHC_LOWER_EXPR_FLOW_H

#include "ast_to_hir/AST_lower_expr.h"

class Lower_expr_flow : public AST::Lower_expr
{
public:
	AST::Expr* post_bin_op(AST::Bin_op* in);
	AST::Expr* post_conditional_expr(AST::Conditional_expr* in);
};

#endif // PHC_LOWER_EXPR_FLOW_H
