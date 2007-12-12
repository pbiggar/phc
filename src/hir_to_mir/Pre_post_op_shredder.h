/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert pre- and post-ops to just pre-ops.
 */

#ifndef PHC_PRE_POST_OP_SHREDDER_H
#define PHC_PRE_POST_OP_SHREDDER_H

#include "HIR_lower_expr.h"
#include "process_ir/fresh.h"
#include "process_ast/Invalid_check.h"


class Pre_post_op_shredder : public Lower_expr
{
	HIR::Expr* post_pre_op(HIR::Pre_op* in);
	void pre_eval_expr (HIR::Eval_expr* in, List<HIR::Statement*>* out);
	HIR::Expr* post_post_op(HIR::Post_op* in);
};

#endif // PHC_PRE_POST_OP_SHREDDER_H
