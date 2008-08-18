/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower control flow inside expressions (",", "&&", "||", "?:") 
 */

#include "Lower_expr_flow.h"
#include "process_ir/General.h"

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
 * 		foo((bool)($TEF1 ? $TEF1 : g()));
 *
 * Convert
 * 		foo(f() && g());
 * into
 * 		$TEF1 = f();
 * 		foo((bool)($TEF1 ? g() : $TEF1));
 *
 * The conditional expressions are then taken care of by post_conditional_expr
 */

Expr* Lower_expr_flow::post_bin_op(Bin_op* in)
{
	Conditional_expr* result;
	if(*in->op->value == ",")
	{
		pieces->push_back(new Eval_expr(in->left));
		return in->right;
	}
	else if(*in->op->value == "||" || *in->op->value == "or")
	{
		Variable* temp = dynamic_cast<Variable*>(eval(in->left));
		assert(temp);
		result = new Conditional_expr(
			temp->clone(), 
			temp->clone(),
			in->right);
	}
	else if(*in->op->value == "&&" || *in->op->value == "and")
	{
		Variable* temp = dynamic_cast<Variable*>(eval(in->left));
		assert(temp);
		result = new Conditional_expr (
			temp->clone(), 
			in->right,
			temp->clone());
	}
	else 
		return in;

	// && and || automatically turn their parameters into bools
	return new Cast (new CAST (s("bool")), post_conditional_expr (result));
}

/*
 * Translate
 * 		foo(f() ? g() : h());
 * into
 * 		if(f()) $TEF2 = g ();
 * 		else $TEF2 = h ();
 *			foo($TEF2);
 */

Expr* Lower_expr_flow::post_conditional_expr(Conditional_expr* in)
{
	Variable* temp = fresh_var("TEF");

	pieces->push_back(new If (
		in->cond, 
			new Statement_list (
				new Eval_expr (
					new Assignment (
						temp->clone (), 
						false, 
						in->iftrue))),
			new Statement_list (
				new Eval_expr (
					new Assignment (
						temp->clone (),
						false,
						in->iffalse)))));
	
	return temp;
}
