/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generic superclass for transformations that replace expressions
 * by multiple statements
 */

#include "AST_lower_expr.h"
#include "process_ir/fresh.h"
#include "process_ir/General.h"

using namespace AST;

void Lower_expr::children_php_script(PHP_script* in)
{
	pieces = new Statement_list;
	Transform::children_php_script(in);
}

/*
 * For each statement that contains an expression, we push back the
 * pieces created for each part of the expression.
 */

void Lower_expr::post_eval_expr (Eval_expr* in, Statement_list* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_global (Global* in, Statement_list* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_return (Return* in, Statement_list* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_continue (Continue* in, Statement_list* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_break (Break* in, Statement_list* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_throw (Throw* in, Statement_list* out)
{
	push_back_pieces(in, out);
}

/*
 * For each control-flow statement that contains an expression, we
 * push back the pieces created for each part of the expression, but
 * before the statement, since it can contain sub-statements.
 */

/* Avoid putting the pieces from the expression into the body */
void Lower_expr::children_if (If* in)
{
	// save the expression's pieces
	in->expr = transform_expr(in->expr);
	Statement_list* saved_pieces = pieces;
	pieces = new Statement_list ();

	// run the rest of the transform
	in->iftrue = transform_statement_list(in->iftrue);
	in->iffalse = transform_statement_list(in->iffalse);

	// restore the pieces for post_if
	pieces = saved_pieces;
}

void Lower_expr::post_if (If* in, Statement_list* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::children_while (While* in)
{
	// save the expression's pieces
	in->expr = transform_expr(in->expr);
	Statement_list* saved_pieces = pieces;
	pieces = new Statement_list;

	// run the rest of the transform
	in->statements = transform_statement_list(in->statements);

	// restore the pieces for post_while
	pieces = saved_pieces;
}

void Lower_expr::post_while (While* in, Statement_list* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::children_foreach (Foreach* in)
{
	// save the expression's pieces
	in->expr = transform_expr(in->expr);

	// No need to mess with the key and val, as they are written to,
	// not read from. Early_lower_control_flow deals with them.

	Statement_list* saved_pieces = pieces;
	pieces = new Statement_list;

	// run the rest of the transform
	in->statements = transform_statement_list(in->statements);

	// restore the pieces for post_foreach
	pieces = saved_pieces;
}

void Lower_expr::post_foreach (Foreach* in, Statement_list* out)
{
	push_back_pieces(in, out);
}



void Lower_expr::push_back_pieces(Statement* in, Statement_list* out)
{
	out->push_back_all(pieces);
	out->push_back(in);

	// Move comment to the first piece (if any)
	if(!pieces->empty())
	{
		pieces->front()->attrs->set("phc.comments", in->get_comments());
		in->attrs->set("phc.comments", new String_list);
	}

	pieces->clear();
}

/*
 * A common pattern is captured by "eval", which takes an argument
 * an expression e, generates a new temporary T, and pushes back the
 * statement
 *  
 *   T = e;
 *
 * the value returned is the expression "T". 
 *
 * If the node is marked "phc.lower_expr.no_temp", eval simply
 * returns in.
 */

Expr* Lower_expr::eval(Expr* in)
{
	if(in->attrs->is_true("phc.ast_lower_expr.no_temp"))
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
