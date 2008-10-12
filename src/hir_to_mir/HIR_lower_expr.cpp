/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generic superclass for transformations that replace expressions by
 * multiple statements
 */

#include "HIR_lower_expr.h"
#include "process_ir/fresh.h"

using namespace HIR;

void Lower_expr::children_php_script(PHP_script* in)
{
	pieces = new Statement_list;
	Transform::children_php_script(in);
}

/*
 * For each statement that contains an expression, we push back the
 * pieces created for each part of the expression.
 *
 * Note that we assume that control flow has been lowered, so there is
 * only a limited number of statements to consider here.
 */

void Lower_expr::post_assign_var (Assign_var* in, Statement_list* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_assign_var_var (Assign_var_var* in, Statement_list* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_assign_array (Assign_array* in, Statement_list* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_assign_next (Assign_next* in, Statement_list* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_eval_expr (Eval_expr* in, Statement_list* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_return(Return* in, Statement_list* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_global(Global* in, Statement_list* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::push_back_pieces(Statement* in, Statement_list* out)
{
	out->push_back_all(pieces);
	out->push_back(in);

	pieces->clear();
}

/*
 * A common pattern is captured by "eval", which takes an argument
 * an expression e, generates a new temporary T, and pushes back the statement
 *  
 *   T = e;
 *
 * the value returned is the expression "T". 
 *
 * If the node is marked "phc.hir_lower_expr.no_temp", eval simply returns in.
 */

VARIABLE_NAME* Lower_expr::eval(Expr* in)
{
	VARIABLE_NAME* temp = fresh_var_name("TLE"); 
	eval (in, temp);
	return temp;
}

void Lower_expr::eval(Expr* in, VARIABLE_NAME* temp)
{
	pieces->push_back(
		new Assign_var (
				temp->clone (),
				in->clone ()));
}
