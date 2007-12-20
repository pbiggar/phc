/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower control flow inside expressions (",", "&&", "||", "?:") 
 */

#include "Lower_expr_flow.h"
#include "process_ir/fresh.h"

using namespace AST;

/*
 * Binary operator
 *
 * Convert 
 *		foo(f(), g());
 * into
 *		f();
 *		foo(g());
 *
 * Convert
 * 		foo(f() || g());
 * into
 * 		$TEF1 = f();
 * 		foo($TEF1 ? $TEF1 : g());
 *
 * Convert
 * 		foo(f() && g());
 * into
 * 		$TEF1 = g();
 * 		foo($TEF1 ? g() : $TEF1);
 *
 * The conditional expressions are then taken care of by post_conditional_expr
 */

Expr* Lower_expr_flow::post_bin_op(Bin_op* in)
{
	if(*in->op->value == ",")
	{
		pieces->push_back(new Eval_expr(in->left));
		return in->right;
	}
	else if(*in->op->value == "||" || *in->op->value == "or")
	{
		Variable* temp = dynamic_cast<Variable*>(eval(in->left));
		assert(temp);
		return post_conditional_expr(new Conditional_expr(
			temp->clone(), temp->clone(), in->right));
	}
	else if(*in->op->value == "&&" || *in->op->value == "and")
	{
		Variable* temp = dynamic_cast<Variable*>(eval(in->left));
		assert(temp);
		return post_conditional_expr(new Conditional_expr(
			temp->clone(), in->right, temp->clone()));
	}
	else 
		return in;
}

/*
 * Translate
 * 		foo(f() ? g() : h());
 * into
 * 		if(f()) $TEF2 = g ();
 * 		else $TEF2 = h ();
 *  	foo($TEF2);
 */

Expr* Lower_expr_flow::post_conditional_expr(Conditional_expr* in)
{
	Variable* temp = fresh_var("TEF");

	pieces->push_back(new If (in->cond, 
		new List<Statement*> (new Eval_expr (new Assignment (temp->clone (), false, in->iftrue))),
		new List<Statement*> (new Eval_expr (new Assignment (temp->clone (), false, in->iffalse)))));
	
	return temp;
}
