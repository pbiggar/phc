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
	pieces = new List<Statement*>;
	Transform::children_php_script(in);
}

/*
 * For each statement that contains an expression, we push back the
 * pieces created for each part of the expression.
 *
 * Note that we assume that control flow has been lowered, so there is
 * only a limited number of statements to consider here.
 */

void Lower_expr::post_eval_expr(Eval_expr* in, List<Statement*>* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_return(Return* in, List<Statement*>* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_branch(Branch* in, List<Statement*>* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_global(Global* in, List<Statement*>* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::push_back_pieces(Statement* in, List<Statement*>* out)
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

// TODO we ignore the results of Annotate here, even though they're relevant
Expr* Lower_expr::eval(Expr* in)
{
	// TODO what if its already a var
	if(in->attrs->is_true("phc.hir_lower_expr.no_temp"))
	{
		assert (false);
		return in;
	}
	else
	{
		Variable* temp = fresh_var("TLE"); 
		eval(in, temp);
		return temp;
	}
}

// Variation on eval that takes in the name of the temp
void Lower_expr::eval(Expr* in, Variable* temp)
{
	pieces->push_back(new Eval_expr(new Assignment(temp->clone (), false, in->clone ())));
}


VARIABLE_NAME* Lower_expr::eval_var(Expr* in)
{
	if(in->attrs->is_true("phc.hir_lower_expr.no_temp"))
	{
		// TODO
		assert (false); 
		return NULL;
	}
	else
	{
		VARIABLE_NAME* temp = fresh_var_name("TLE"); 
		eval_var(in, temp);
		return temp;
	}
}

void Lower_expr::eval_var(Expr* in, VARIABLE_NAME* temp)
{
	pieces->push_back(new Eval_expr(new Assignment(
		new Variable (NULL, temp->clone (), new List<Expr*>),
		false, 
		in->clone ())));
}


