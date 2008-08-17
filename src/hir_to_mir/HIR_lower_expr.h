/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generic superclass for transformations that replace expressions by
 * multiple statements
 */

#ifndef PHC_HIR_LOWER_EXPR_H
#define PHC_HIR_LOWER_EXPR_H

#include "HIR_transform.h"

namespace HIR 
{
	class Lower_expr : public HIR::Transform
	{
	public:
		void children_php_script(HIR::PHP_script* in);

	public:
		void post_assign_var (HIR::Assign_var* in, List<HIR::Statement*>* out);
		void post_assign_var_var (HIR::Assign_var_var* in, List<HIR::Statement*>* out);
		void post_assign_array (HIR::Assign_array* in, List<HIR::Statement*>* out);
		void post_push_array (HIR::Push_array* in, List<HIR::Statement*>* out);
		void post_return(HIR::Return* in, List<HIR::Statement*>* out);
		void post_global(HIR::Global* in, List<HIR::Statement*>* out);
		void post_eval_expr (HIR::Eval_expr* in, List<Statement*>* out);

	protected:
		HIR::VARIABLE_NAME* eval (HIR::Expr* in);
		void eval (HIR::Expr* in, HIR::VARIABLE_NAME* temp);
		void push_back_pieces(HIR::Statement* in, List<HIR::Statement*>* out);
		List<HIR::Statement*>* pieces;
	};

}

#endif // PHC_HIR_LOWER_EXPR_H
