/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generic superclass for transformations that replace expressions by
 * multiple statements
 */

#include "Lower_expr.h"
#include "fresh.h"

void Lower_expr::children_php_script(AST_php_script* in)
{
	pieces = new List<AST_statement*>;
	AST_transform::children_php_script(in);
}

/*
 * For each statement that contains an expression, we push back the
 * pieces created for each part of the expression.
 *
 * Note that we assume that control flow has been lowered, so there is
 * only a limited number of statements to consider here.
 */

void Lower_expr::post_eval_expr(AST_eval_expr* in, List<AST_statement*>* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_return(AST_return* in, List<AST_statement*>* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_branch(AST_branch* in, List<AST_statement*>* out)
{
	push_back_pieces(in, out);
}

void Lower_expr::post_global(AST_global* in, List<AST_statement*>* out)
{
	List<AST_variable_name*>::const_iterator i;
	i = in->variable_names->begin();

	AST_global* first_global = new AST_global(new List<AST_variable_name*>(*i));
	push_back_pieces(first_global, out);

	// Generate a new global statement for all remaining variables 
	for(i++; i != in->variable_names->end(); i++)
	{
		out->push_back(new AST_global(new List<AST_variable_name*>(*i)));
	}
}

void Lower_expr::push_back_pieces(AST_statement* in, List<AST_statement*>* out)
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

AST_expr* Lower_expr::eval(AST_expr* in)
{
	if(in->attrs->is_true("phc.lower_expr.no_temp"))
	{
		return in;
	}
	else
	{
		AST_variable* temp = fresh_var("TLE"); 
		eval(in, temp);
		return temp;
	}
}

// Variation on eval that takes in the name of the temp
void Lower_expr::eval(AST_expr* in, AST_variable* temp)
{
	pieces->push_back(new AST_eval_expr(new AST_assignment(temp->clone (), false, in->clone ())));
}
