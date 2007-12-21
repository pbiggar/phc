/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * shredder (n.): a machine that tears objects into smaller pieces.
 * (Transform the HIR into 3AC-like code)
 */

#ifndef PHC_HIR_SHREDDER_H
#define PHC_HIR_SHREDDER_H

#include "HIR_lower_expr.h"

namespace HIR
{
	class Shredder : public Lower_expr
	{
	public:
		void post_nop(Nop* in);

	public:
		Expr* post_new (New* in);
		Expr* post_bin_op(Bin_op* in);
		Expr* post_unary_op(Unary_op* in);
		Expr* post_cast(Cast* in);
		Expr* post_instanceof(Instanceof* in);
		Expr* post_method_invocation(Method_invocation* in);
		Expr* post_int(INT* in);
		Expr* post_real(REAL* in);
		Expr* post_bool(BOOL* in);
		Expr* post_string(STRING* in);
		Expr* post_nil(NIL* in);
		Expr* post_constant (Constant* in);
		Expr* post_foreach_has_key (Foreach_has_key* in);
		Expr* post_array(Array* in);
		Expr* post_assignment(Assignment* in);
		Expr* post_op_assignment(Op_assignment* in);
		Expr* pre_ignore_errors(Ignore_errors* in);
		Expr* post_ignore_errors(Ignore_errors* in);
		void pre_eval_expr (Eval_expr* in, List<Statement*>* out);
	};

}


#endif // PHC_HIR_SHREDDER_H
