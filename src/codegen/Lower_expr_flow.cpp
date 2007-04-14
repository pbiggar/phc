/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower control flow inside expressions (",", "&&", "||", "?:") 
 */

#include "Lower_expr_flow.h"
#include "fresh.h"

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

AST_expr* Lower_expr_flow::post_bin_op(AST_bin_op* in)
{
	if(*in->op->value == ",")
	{
		pieces->push_back(new AST_eval_expr(in->left));
		return in->right;
	}
	else if(*in->op->value == "||")
	{
		AST_variable* temp = eval(in->left);
		return post_conditional_expr(new AST_conditional_expr(
			temp->clone(), temp->clone(), in->right));
	}
	else if(*in->op->value == "&&")
	{
		AST_variable* temp = eval(in->left); 
		return post_conditional_expr(new AST_conditional_expr(
			temp->clone(), in->right, temp->clone()));
	}
	else 
		return in;
}

/*
 * Translate
 * 		foo(f() ? g() : h());
 * into
 * 		if(f()) goto L1 else goto L2;
 *  L1:
 *  	$TEF2 = g();
 *  	goto L3;
 *  L2:
 *  	$TEF2 = h();
 *  	goto L3;
 *  L3:
 *  	foo($TEF2);
 */

AST_expr* Lower_expr_flow::post_conditional_expr(AST_conditional_expr* in)
{
	Token_label_name* label1 = new Token_label_name(fresh("LEF"));
	Token_label_name* label2 = new Token_label_name(fresh("LEF"));
	Token_label_name* label3 = new Token_label_name(fresh("LEF"));
	AST_variable* temp = fresh_var("TEF");

	pieces->push_back(new AST_branch(in->cond, label1, label2));
	pieces->push_back(new AST_label(label1));
	eval(in->iftrue, temp);
	pieces->push_back(new AST_goto(label3));
	pieces->push_back(new AST_label(label2));
	eval(in->iffalse, temp);
	pieces->push_back(new AST_goto(label3));
	pieces->push_back(new AST_label(label3));
	
	return temp;
}
