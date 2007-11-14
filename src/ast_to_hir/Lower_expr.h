/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generic superclass for transformations that replace expressions by
 * multiple statements
 */

#ifndef PHC_LOWER_EXPR_H
#define PHC_LOWER_EXPR_H

#include "AST_transform.h"

class Lower_expr : public AST::AST_transform
{
public:
	void children_php_script(AST::AST_php_script* in);

public:
	void post_eval_expr(AST::AST_eval_expr* in, List<AST::AST_statement*>* out);
	void post_return(AST::AST_return* in, List<AST::AST_statement*>* out);
	void post_branch(AST::AST_branch* in, List<AST::AST_statement*>* out);
	void post_global(AST::AST_global* in, List<AST::AST_statement*>* out);

protected:
	AST::AST_expr* eval(AST::AST_expr* in);
	void eval(AST::AST_expr* in, AST::AST_variable* temp);
	void push_back_pieces(AST::AST_statement* in, List<AST::AST_statement*>* out);
	List<AST::AST_statement*>* pieces;
};

#endif // PHC_LOWER_EXPR_H
