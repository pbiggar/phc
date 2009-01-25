/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generic superclass for transformations that replace expressions by
 * multiple statements
 */

#ifndef PHC_AST_LOWER_EXPR_H
#define PHC_AST_LOWER_EXPR_H

#include "AST_transform.h"
#include "lib/Stack.h"

namespace AST
{
class Lower_expr : public Transform, virtual public GC_obj
{
public:
	void children_php_script(PHP_script* in);

public:
	void children_if (If* in);
	void post_if (If* in, Statement_list* out);

	void children_while (While* in);
	void post_while (While* in, Statement_list* out);

	void children_foreach (Foreach* in);
	void post_foreach (Foreach* in, Statement_list* out);

	// Switch is already lowered
	// Do is already lowered
	// For is already lowered
	// Try blocks don't have expressions so don't need special treatment
	// Static declarations cannot be lowered

	void post_eval_expr (Eval_expr* in, Statement_list* out);
	void post_return (Return* in, Statement_list* out);
	void post_global (Global* in, Statement_list* out);
	void post_continue (Continue* in, Statement_list* out);
	void post_break (Break* in, Statement_list* out);
	void post_throw (Throw* in, Statement_list* out);

// Common code generation patterns
protected:
	Expr* eval(Expr* in);
	void eval(Expr* in, Variable* temp);

// Define a number of hooks that can be redefined by inheriting classes
// to tweak the behaviour of the transformation
protected:
	virtual void push_back_pieces(Statement* in, Statement_list* out);
	virtual void backup_pieces();
	virtual void restore_pieces();

protected:
	Statement_list* pieces;
	Stack<Statement_list*> pieces_backup;
};
}

#endif // PHC_AST_LOWER_EXPR_H
