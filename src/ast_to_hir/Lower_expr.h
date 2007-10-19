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

using namespace AST;

class Lower_expr : public AST_transform
{
public:
	void children_php_script(AST_php_script* in);

public:
	void post_eval_expr(AST_eval_expr* in, List<AST_statement*>* out);
	void post_return(AST_return* in, List<AST_statement*>* out);
	void post_branch(AST_branch* in, List<AST_statement*>* out);
	void post_global(AST_global* in, List<AST_statement*>* out);

protected:
	AST_expr* eval(AST_expr* in);
	void eval(AST_expr* in, AST_variable* temp);
	void push_back_pieces(AST_statement* in, List<AST_statement*>* out);
	List<AST_statement*>* pieces;
};

#endif // PHC_LOWER_EXPR_H
