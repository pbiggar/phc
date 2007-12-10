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

class Lower_expr : public AST::Transform
{
public:
	void children_php_script(AST::PHP_script* in);

public:
	void post_eval_expr(AST::Eval_expr* in, List<AST::Statement*>* out);
	void post_return(AST::Return* in, List<AST::Statement*>* out);
	void post_branch(AST::Branch* in, List<AST::Statement*>* out);
	void post_global(AST::Global* in, List<AST::Statement*>* out);

protected:
	AST::Expr* eval(AST::Expr* in);
	void eval(AST::Expr* in, AST::Variable* temp);
	void push_back_pieces(AST::Statement* in, List<AST::Statement*>* out);
	List<AST::Statement*>* pieces;
};

#endif // PHC_LOWER_EXPR_H
