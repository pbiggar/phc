/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert pre- and post-ops to just pre-ops.
 */

#ifndef PHC_PRE_POST_OP_SHREDDER_H
#define PHC_PRE_POST_OP_SHREDDER_H

#include "ast_to_hir/AST_lower_expr.h"

using namespace AST;

class Pre_post_op_shredder : public Lower_expr
{
public:
	void children_php_script(PHP_script* in);

public:
	Expr* post_pre_op(Pre_op* in);
	Expr* post_post_op(Post_op* in);

public:
	void post_return(Return* in, Statement_list* out);
	void post_continue(Continue* in, Statement_list* out);
	void post_break(Break* in, Statement_list* out);
	void post_throw(Throw* in, Statement_list* out);

protected:
	void push_back_pieces(Statement* in, Statement_list* out);
	void open_scope();
	void close_scope();
	Statement_list* transform_body(Statement_list* in);

protected:
	Statement_list* post_pieces;
	Stack<Statement_list*> post_pieces_backup;
	virtual void clear_post_pieces(Expr** in);
};

#endif // PHC_PRE_POST_OP_SHREDDER_H
