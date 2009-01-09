/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert pre- and post-ops to just pre-ops.
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
