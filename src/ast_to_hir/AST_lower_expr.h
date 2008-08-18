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

namespace AST
{
	class Lower_expr : public Transform
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

		// TODO: We handle most Statement types here. What about try, throw and
		// static_declaration?

		void post_eval_expr (Eval_expr* in, Statement_list* out);
		void post_return (Return* in, Statement_list* out);
		void post_global (Global* in, Statement_list* out);
		void post_continue (Continue* in, Statement_list* out);
		void post_break (Break* in, Statement_list* out);
		void post_throw (Throw* in, Statement_list* out);

	protected:
		Expr* eval(Expr* in);
		void eval(Expr* in, Variable* temp);
		void push_back_pieces(Statement* in, Statement_list* out);
		Statement_list* pieces;
	};

}

#endif // PHC_AST_LOWER_EXPR_H
