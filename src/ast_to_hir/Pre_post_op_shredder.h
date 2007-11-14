/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert pre- and post-ops to just pre-ops.
 */

#ifndef PHC_PRE_POST_OP_SHREDDER_H
#define PHC_PRE_POST_OP_SHREDDER_H

#include "Lower_expr.h"
#include "fresh.h"
#include "process_ast/Invalid_check.h"


class Pre_post_op_shredder : public Lower_expr
{
	AST::AST_expr* post_pre_op(AST::AST_pre_op* in);
	void pre_eval_expr (AST::AST_eval_expr* in, List<AST::AST_statement*>* out);
	AST::AST_expr* post_post_op(AST::AST_post_op* in);
};

#endif // PHC_PRE_POST_OP_SHREDDER_H
