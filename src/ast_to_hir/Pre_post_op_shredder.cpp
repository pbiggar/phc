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
	pieces->push_back (new Eval_expr (
					in));

	// $x
	return in->variable->clone ();
}

/*
 * For a post-op, add the post-op to post-pieces so it evaluated after
 * the expression proper.
 */

Expr* Pre_post_op_shredder::post_post_op(Post_op* in)
{
	post_pieces->push_back (new Eval_expr (
					new Pre_op (
						in->op,
						in->variable)));

	return in->variable->clone();
}

/*
 * Control flow constructs 
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
	if(post_pieces->size() > 0)
	{
		*in = eval(*in);
		pieces->push_back_all(post_pieces);
		post_pieces->clear();
	}
}

/*
 * Administration
 */

void Pre_post_op_shredder::push_back_pieces(Statement* in, Statement_list* out)
{
	// If there are any post_pieces left, that means that the statement they
	// were in was not a control flow construct (since then the post_pieces
	// would have been cleared by close_scope, below). We simply add them
	// to *out. Since they should be evaluated *after* the expression, we
	// add them after the other pieces. 
	Lower_expr::push_back_pieces(in, out);
	out->push_back_all(post_pieces);
	post_pieces->clear();
}

void Pre_post_op_shredder::open_scope()
{
	post_pieces_backup.push(post_pieces);
	post_pieces = new Statement_list;
	Lower_expr::open_scope();
}

void Pre_post_op_shredder::close_scope()
{
	// The post_pieces have been added to the pieces of the bodies and
	// do not need to be kept anymore
	post_pieces->clear();
	post_pieces_backup.pop();
	Lower_expr::close_scope();
}

Statement_list* Pre_post_op_shredder::transform_body(Statement_list* in)
{
	// Push back the statements that are yet to be processed to the pieces
	// of each body
	Statement_list* result = Lower_expr::transform_body(in);
	result->push_front_all(post_pieces_backup.top());
	return result;
}
