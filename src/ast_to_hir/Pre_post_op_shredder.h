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
public:

	/* Convert
	 *		++$x;
	 *	into
	 *		$u = ++$x; // mark $u as unused
	 *		$x;
	 */
	AST_expr* post_pre_op(AST_pre_op* in)
	{
		// $u = ++$x;
		AST_variable* unused = fresh_var ("TSpri");
		unused->attrs->set_true ("phc.codegen.unused");
		pieces->push_back (new AST_eval_expr (
				new AST_assignment (
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
	void pre_eval_expr (AST_eval_expr* in, List<AST_statement*>* out)
	{
		if (AST_post_op* post_op = dynamic_cast<AST_post_op*> (in->expr))
		{
			in->expr = new AST_pre_op (post_op->op, post_op->variable);
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
	AST_expr* post_post_op(AST_post_op* in)
	{
		AST_variable* old_value = fresh_var("TS");

		// $t = $x
		pieces->push_back (new AST_eval_expr (new AST_assignment(
						old_value->clone (),
						false,
						in->variable->clone())));

		// $u = ++$x;
		AST_variable* unused = fresh_var ("TSpoi");
		unused->attrs->set_true ("phc.codegen.unused");
		pieces->push_back (new AST_eval_expr (
				new AST_assignment (
					unused,
					false,
					new AST_pre_op (
						in->op,
						in->variable))));

		// $t
		return old_value;
	}

};

#endif // PHC_PRE_POST_OP_SHREDDER_H
