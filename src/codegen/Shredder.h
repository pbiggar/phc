/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * shredder (n.): a machine that tears objects into smaller pieces.
 * (Transform the AST into 3AC-like code)
 */

#ifndef PHC_SHREDDER_H
#define PHC_SHREDDER_H

#include "AST_transform.h"

class Shredder : public AST_transform
{
public:
	Shredder();

public:
	void post_eval_expr(AST_eval_expr* in, List<AST_statement*>* out);
	void post_return(AST_return* in, List<AST_statement*>* out);

public:
	AST_variable* post_variable(AST_variable* in);
	AST_expr* post_bin_op(AST_bin_op* in);
	AST_expr* post_pre_op(AST_pre_op* in);
	AST_expr* post_post_op(AST_post_op* in);
	AST_expr* post_unary_op(AST_unary_op* in);
	AST_expr* post_int(Token_int* in);
	AST_expr* post_real(Token_real* in);
	AST_expr* post_bool(Token_bool* in);
	AST_expr* post_string(Token_string* in);
	AST_expr* post_null(Token_null* in);
	Token_method_name* post_method_name(Token_method_name* in);

protected:
	List<AST_statement*>* pieces;
	AST_variable* create_piece(AST_expr* in);
	void push_back_pieces(AST_statement* in, List<AST_statement*>* out);
};

#endif // PHC_SHREDDER_H
