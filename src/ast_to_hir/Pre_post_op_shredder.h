/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert pre- and post-ops to just pre-ops.
 */

#ifndef PHC_PRE_POST_OP_SHREDDER_H
#define PHC_PRE_POST_OP_SHREDDER_H

#include "ast_to_hir/AST_lower_expr.h"
#include "process_ir/fresh.h"


class Pre_post_op_shredder : public AST::Lower_expr
{
	AST::Expr* post_pre_op(AST::Pre_op* in);
	void pre_eval_expr (AST::Eval_expr* in, AST::Statement_list* out);
	AST::Expr* post_post_op(AST::Post_op* in);
};

#endif // PHC_PRE_POST_OP_SHREDDER_H
