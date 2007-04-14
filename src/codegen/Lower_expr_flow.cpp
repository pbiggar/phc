/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower control flow inside expressions (",", "&&", "||", "?:") 
 */

#include "Lower_expr_flow.h"

Lower_expr_flow::Lower_expr_flow()
{
	pieces = new List<AST_statement*>;
}

/*
 * After lowering, only a few statements are left that contain expressions
 */

void Lower_expr_flow::post_branch(AST_branch* in, List<AST_statement*>* out)
{
	out->push_back_all(pieces);
	out->push_back(in);
	pieces->clear();
}

void Lower_expr_flow::post_eval_expr(AST_eval_expr* in, List<AST_statement*>* out)
{
	out->push_back_all(pieces);
	out->push_back(in);
	pieces->clear();
}

/*
 * Binary operator
 */

AST_expr* Lower_expr_flow::post_bin_op(AST_bin_op* in)
{
	if(*in->op->value == ",")
	{
		// Evaluate LHS first
		pieces->push_back(new AST_eval_expr(in->left));
		// Result is RHS
		return in->right;
	}

	return in;
}
