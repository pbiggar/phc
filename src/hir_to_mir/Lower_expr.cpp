/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generic superclass for transformations that replace expressions by
 * multiple statements
 */

#include "Lower_expr.h"
#include "fresh.h"

using namespace AST;

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

	// Move comment to the first piece (if any)
	if(!pieces->empty())
	{
		pieces->front()->attrs->set("phc.comments", in->get_comments());
		in->attrs->set("phc.comments", new List<String*>);
	}

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
 * If the node is marked "phc.lower_expr.no_temp", eval simply returns in.
 */

Expr* Lower_expr::eval(Expr* in)
{
	if(in->attrs->is_true("phc.lower_expr.no_temp"))
	{
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
