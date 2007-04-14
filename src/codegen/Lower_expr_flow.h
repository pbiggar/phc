/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower control flow inside expressions (",", "&&", "||", "?:") 
 */

#ifndef PHC_LOWER_EXPR_FLOW_H
#define PHC_LOWER_EXPR_FLOW_H

#include "AST_transform.h"

class Lower_expr_flow : public AST_transform
{
public:
	Lower_expr_flow();

public:
	void post_branch(AST_branch* in, List<AST_statement*>* out);
	void post_eval_expr(AST_eval_expr* in, List<AST_statement*>* out);

public:
	AST_expr* post_bin_op(AST_bin_op* in);

protected:
	List<AST_statement*>* pieces;
};

#endif // PHC_LOWER_EXPR_FLOW_H
