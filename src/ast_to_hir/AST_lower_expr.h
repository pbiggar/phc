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
		void post_if (If* in, List<Statement*>* out);

		void children_while (While* in);
		void post_while (While* in, List<Statement*>* out);

		void children_foreach (Foreach* in);
		void post_foreach (Foreach* in, List<Statement*>* out);

		// Switch is already lowered
		// Do is already lowered
		// For is already lowered

		// TODO: We handle most Statement types here. What about try, throw and
		// static_declaration?

		void post_eval_expr (Eval_expr* in, List<Statement*>* out);
		void post_return (Return* in, List<Statement*>* out);
		void post_global (Global* in, List<Statement*>* out);
		void post_continue (Continue* in, List<Statement*>* out);
		void post_break (Break* in, List<Statement*>* out);
		void post_throw (Throw* in, List<Statement*>* out);

	protected:
		Expr* eval(Expr* in);
		void eval(Expr* in, Variable* temp);
		void push_back_pieces(Statement* in, List<Statement*>* out);
		List<Statement*>* pieces;
	};

}

#endif // PHC_AST_LOWER_EXPR_H
