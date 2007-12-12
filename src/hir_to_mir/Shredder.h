/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * shredder (n.): a machine that tears objects into smaller pieces.
 * (Transform the HIR into 3AC-like code)
 */

#ifndef PHC_SHREDDER_H
#define PHC_SHREDDER_H

#include "HIR.h"
#include "HIR_lower_expr.h"

List<HIR::Statement*>* shred (HIR::Statement* in);

class Shredder : public Lower_expr
{
public:
	void children_php_script(HIR::PHP_script* in);
	void post_nop(HIR::Nop* in);

public:
	HIR::Variable* post_variable(HIR::Variable* in);
	HIR::Expr* post_new (HIR::New* in);
	HIR::Expr* post_bin_op(HIR::Bin_op* in);
	HIR::Expr* post_unary_op(HIR::Unary_op* in);
	HIR::Expr* post_cast(HIR::Cast* in);
	HIR::Expr* post_instanceof(HIR::Instanceof* in);
	HIR::Expr* post_method_invocation(HIR::Method_invocation* in);
	HIR::Expr* post_int(HIR::INT* in);
	HIR::Expr* post_real(HIR::REAL* in);
	HIR::Expr* post_bool(HIR::BOOL* in);
	HIR::Expr* post_string(HIR::STRING* in);
	HIR::Expr* post_nil(HIR::NIL* in);
	HIR::Expr* post_constant (HIR::Constant* in);
	HIR::Expr* post_foreach_has_key (HIR::Foreach_has_key* in);
	HIR::Expr* post_array(HIR::Array* in);
	HIR::Expr* post_assignment(HIR::Assignment* in);
	HIR::Expr* post_op_assignment(HIR::Op_assignment* in);
	HIR::Expr* pre_ignore_errors(HIR::Ignore_errors* in);
	HIR::Expr* post_ignore_errors(HIR::Ignore_errors* in);
	void pre_eval_expr (HIR::Eval_expr* in, List<HIR::Statement*>* out);
};


#endif // PHC_SHREDDER_H
