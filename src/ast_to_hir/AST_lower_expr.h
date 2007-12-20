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
		void post_eval_expr(Eval_expr* in, List<Statement*>* out);
		void post_return(Return* in, List<Statement*>* out);
		void post_branch(Branch* in, List<Statement*>* out);
		void post_global(Global* in, List<Statement*>* out);

	protected:
		Expr* eval(Expr* in);
		void eval(Expr* in, Variable* temp);
		void push_back_pieces(Statement* in, List<Statement*>* out);
		List<Statement*>* pieces;
	};

}

#endif // PHC_AST_LOWER_EXPR_H
