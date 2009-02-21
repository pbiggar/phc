/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert pre- and post-ops to just pre-ops.
 *
 * Consider
 * 
 *   print($i++ < 9);
 *
 * There are (at least) three ways to lower this statement.
 *
 *   print($i < 9);    $T = $i;          $T = $i < 9;
 *   ++$i;             ++$i;             ++$i;
 *                     print($T < 9);    print($T);
 *
 * The first one is the most obvious, but is also the more difficult in the
 * general case. Consider
 * 
 *   if($i++ < 9) { s1 } else { s2 }
 *
 * Option (1) requires pushing the ++$i into both branches:
 *
 *   if($i < 9) { ++$i; s1 } else { ++$i; s2 }
 *
 * However, this is still better than option (2), which puts $i in a
 * copy-on-write set with $T:
 *
 *   $T = $i;
 *   ++$i;
 *   if($T < 9) { s1 } else { s2 }
 *
 * The increment of $i causes $i to be separated from $T; if this occurs in a
 * loop (at it while might, see for example the bench_strcat test; the
 * loop_separation1 tests this explicitly); this is a significant performance
 * penalty (up to 40%). Option (3) here is acceptable:
 *
 *   $T = $i < 9;
 *   ++$i;
 *   if($T) { s1 } else { s2 }
 *
 * since it does not have the separation problem, but there are other examples
 * (loop_separation2) where option (3) has the same negative behaviour as
 * option (2). For example,
 *
 *   if($i--) { s1 } else { s2 }
 *
 * Applying technique (3) to this example yields
 *
 *   $T = $i;
 *   --$i;
 *   if($T) { s1 } else { s2 }
 *
 * Hence, it is better to try and avoid putting the condition in a temp so that
 * option (1) is the preferred option (it is also the most natural option for
 * non-control flow constructs).
 *
 * Unfortunately, this is not always possible. Consider:
 *
 *   return $i++ * 2;
 *
 * (post_increment_in_return test). Applying option (1) here naively yields
 *
 *   return $i * 2;
 *   ++$i;
 *
 * which obviously is no use. Unfortunately, option (1) *cannot* be applied
 * in this case, and we have to resort to option (2) or (3); option (3) will
 * cause fewer separation problems than (2) and so is preferred.
 *
 * Finally, note that all three options (1, 2, 3) will cause duplication of
 * side effects if $i is not a simple variable but something of the form
 * $i[f()], for instance. However, this pass will run after the shredder so that
 * this situation should not arise.
 */

#include "Pre_post_op_shredder.h"
#include "process_ir/fresh.h"

using namespace AST;

void Pre_post_op_shredder::children_php_script(PHP_script* in)
{
	post_pieces = new Statement_list;
	Lower_expr::children_php_script(in);	
}

/*
 * For a pre-op, add the pre-op to pieces so it evaluated before the
 * expression proper.
 */

Expr* Pre_post_op_shredder::post_pre_op(Pre_op* in)
{
	// ++$x;
	pieces->push_back(new Eval_expr(in));

	// $x
	return in->variable->clone ();
}

/*
 * For a post-op, add the post-op to post-pieces so it evaluated after
 * the expression proper.
 */

Expr* Pre_post_op_shredder::post_post_op(Post_op* in)
{
	post_pieces->push_back(new Eval_expr(
					new Pre_op(
						in->op,
						in->variable)));

	return in->variable->clone();
}

/*
 * For Eval_expr we can execute the post-op after the expression is evaluated
 * (option 1, above)
 */

void Pre_post_op_shredder::post_eval_expr(Eval_expr* in, Statement_list* out)
{
	// clear the post_pieces before calling post_back_pieces to avoid an
	// assertion failure
	Statement_list* eval_post_pieces = post_pieces;
	post_pieces = new Statement_list;

	Lower_expr::push_back_pieces(in, out);
	out->push_back_all(eval_post_pieces);
}

/*
 * For If-statements we push the post-op into both branches of the if
 */

void Pre_post_op_shredder::children_if(If* in)
{
	in->expr = transform_expr(in->expr);

	Statement_list* if_post_pieces = post_pieces;
	post_pieces = new Statement_list;

	backup_pieces();
	in->iftrue = transform_statement_list(in->iftrue);
	in->iffalse = transform_statement_list(in->iffalse);
	restore_pieces();

	in->iftrue->push_front_all(if_post_pieces->clone());
	in->iffalse->push_front_all(if_post_pieces);
}

/*
 * Control flow constructs (option 3, above)
 */

void Pre_post_op_shredder::post_return(Return* in, Statement_list* out)
{
	clear_post_pieces(&in->expr);
	Lower_expr::post_return(in, out);
}

void Pre_post_op_shredder::post_continue(Continue* in, Statement_list* out)
{
	clear_post_pieces(&in->expr);
	Lower_expr::post_continue(in, out);
}

void Pre_post_op_shredder::post_break(Break* in, Statement_list* out)
{
	clear_post_pieces(&in->expr);
	Lower_expr::post_break(in, out);
}

void Pre_post_op_shredder::post_throw(Throw* in, Statement_list* out)
{
	clear_post_pieces(&in->expr);
	Lower_expr::post_throw(in, out);
}

void Pre_post_op_shredder::clear_post_pieces(Expr** in)
{
	if(!post_pieces->empty())
	{
		*in = eval(*in);
		pieces->push_back_all(post_pieces->clone());
		post_pieces->clear();
	}
}

/*
 * We can deal with whiles if necessary but we don't have to: while loops have
 * already been lowered into a 
 * while(True) { ... if(..) break; ... } structure
 *	
 * There really shouldn't be any any pre or post-ops in the expression of a
 * foreach loop, but even if there are, they should already have been lowered
 */

void Pre_post_op_shredder::post_while(While* in, Statement_list* out)
{
	assert(post_pieces->empty());
	Lower_expr::post_while(in, out);
}

void Pre_post_op_shredder::post_foreach(Foreach* in, Statement_list* out)
{
	assert(post_pieces->empty());
	Lower_expr::post_foreach(in, out);
}

/*
 * Administration: add assertions that the post-pieces are handled elsewhere
 */

void Pre_post_op_shredder::push_back_pieces(Statement* in, Statement_list* out)
{
	assert(post_pieces->empty());
	Lower_expr::push_back_pieces(in, out);
}

void Pre_post_op_shredder::backup_pieces()
{
	assert(post_pieces->empty());
	Lower_expr::backup_pieces();
}
