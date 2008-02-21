/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * shredder (n.): a machine that tears objects into smaller pieces.
 * Transform the HIR into 3AC-like code.
 */

#include "HIR_shredder.h"
#include "process_ir/fresh.h"
#include "process_ir/General.h"

using namespace HIR;

/* Remove statements which consist of a single variable. These can be
 * introduced by the list lowering. We use the pre_ form, since the post_ form
 * overrides Lower_expr::post_eval_expr.*/
void Shredder::pre_eval_expr (Eval_expr* in, List<Statement*>* out)
{
	if (in->expr->classid () != Variable::ID)
		out->push_back (in);
}

/*
 * Binary and unary operators
 *
 * The "lazy" binary operators (&&, ||, and friends) are not dealt with here, 
 * but in the lowering pass. Pre and post operators are handled in Early_Shredder.
 */

Expr* Shredder::post_bin_op(Bin_op* in)
{
	return eval(in);
}

Expr* Shredder::post_unary_op(Unary_op* in)
{
	return eval(in);
}

/*
 * Casts
 */

Expr* Shredder::post_cast(Cast* in)
{
	return eval(in);
}

/*
 * instanceof
 */

Expr* Shredder::post_instanceof (Instanceof* in)
{
	return eval(in);
}

/*
 * foreach
 */

Expr* Shredder::post_foreach_has_key (Foreach_has_key* in)
{
	return eval(in);
}

/*
 * Method invocation
 */

Expr* Shredder::post_method_invocation(Method_invocation* in)
{
	return eval(in);
}

Expr* Shredder::post_new (New* in)
{
	return eval(in);
}

/*
 * Literals
 */

Expr* Shredder::post_int(INT* in)
{
	return eval(in);
}

Expr* Shredder::post_real(REAL* in)
{
	return eval(in);
}

Expr* Shredder::post_string(STRING* in)
{
	return eval(in);
}

Expr* Shredder::post_bool(BOOL* in)
{
	return eval(in);
}

Expr* Shredder::post_nil(NIL* in)
{
	return eval(in);
}

Expr* Shredder::post_constant (Constant* in)
{
	return eval(in);
}

/*
 * Translate into canonical tree form (replace assignments within expressions
 * with an assignment and a variable access:
 *
 * Translate
 *
 *	  $x = $y = 5;
 *
 *	into
 *
 *	  $y = 5;
 *	  $t1 = $y;
 *	  $x = $t1;
 */
Expr* Shredder::post_assignment (Assignment* in)
{
	if (in->attrs->is_true ("phc.shredder.non_nested_assignment"))
		return in;

	// dont replace with the same variable, since it may be assigned to multiple
	// times in the same expression.
	pieces->push_back (new Eval_expr (in));
	return eval (in->variable);
}

Expr* Shredder::post_op_assignment(Op_assignment* in)
{
	Assignment* assignment;

	// The LHS may be of the form $x[$y], but that should occur
	// as an operand to a binary operator. Hence, we must visit the RHS again
	// clearing the need_addr flag
	Expr* left = in->variable->clone();
	left->attrs->erase("phc.shredder.need_addr");
	left = transform_expr(left);

	assignment = new Assignment(
		in->variable,
		false,
		new Bin_op(
			left,
			in->op,
			in->expr)
		);
	assignment->attrs = in->attrs;
	
	return post_assignment(assignment); 
}

Expr* Shredder::pre_ignore_errors(Ignore_errors* in)
{
	Variable* zero = fresh_var("TSie");
	Variable* temp = fresh_var("TSie");
	pieces->push_back(new Eval_expr(new Assignment(
		zero,
		false,
		new INT(0))));
	pieces->push_back(new Eval_expr(new Assignment(
		temp,
		false,
		new Method_invocation(
			"error_reporting",
			zero))));
	in->attrs->set("phc.shredder.old_error_level", temp);
	return in;
}

Expr* Shredder::post_ignore_errors(Ignore_errors* in)
{
	Variable* temp = fresh_var("TSie");
	Variable* old = dynamic_cast<Variable*>(in->attrs->get("phc.shredder.old_error_level"));
	assert(old);
	
	pieces->push_back(new Eval_expr(new Assignment(
		temp,
		false,
		new Method_invocation(
			"error_reporting",
			old))));
	
	return in->expr;
}
