/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert pre- and post-ops to just pre-ops.
 */

#include "Pre_post_op_shredder.h"
#include "process_ast/Invalid_check.h"

using namespace HIR;


/* Convert
 *		++$x;
 *	into
 *		$u = ++$x; // mark $u as unused
 *		$x;
 */
Expr* Pre_post_op_shredder::post_pre_op(Pre_op* in)
{
	// $u = ++$x;
	Variable* unused = fresh_var ("TSpri");
	unused->attrs->set_true ("phc.codegen.unused");
	pieces->push_back (new Eval_expr (
				new Assignment (
					unused,
					false,
					in)));

	// $x
	return in->variable->clone ();;
}

/* Special case:
 *	If 
 *		$x++ 
 *	is found on its own, convert directly into
 *		++$x;
 *
 *	This avoids an extra statement being issued by post_post_op.
 *	This should be replaced with data-flow at a later date.
 */
void Pre_post_op_shredder::pre_eval_expr (Eval_expr* in, List<Statement*>* out)
{
	if (Post_op* post_op = dynamic_cast<Post_op*> (in->expr))
	{
		in->expr = new Pre_op (post_op->op, post_op->variable);
	}
	out->push_back (in);
}

/* Convert
 *		$x++;
 *	into
 *		$t = $x;
 *		$u = ++$x; // mark $u as unused
 *		$t;
 */
Expr* Pre_post_op_shredder::post_post_op(Post_op* in)
{
	Variable* old_value = fresh_var("TS");

	// $t = $x
	pieces->push_back (new Eval_expr (new Assignment(
					old_value->clone (),
					false,
					in->variable->clone())));

	// $u = ++$x;
	Variable* unused = fresh_var ("TSpoi");
	unused->attrs->set_true ("phc.codegen.unused");
	pieces->push_back (new Eval_expr (
				new Assignment (
					unused,
					false,
					new Pre_op (
						in->op,
						in->variable))));

	// $t
	return old_value;
}
