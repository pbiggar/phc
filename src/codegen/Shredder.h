/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * shredder (n.): a machine that tears objects into smaller pieces.
 * (Transform the AST into 3AC-like code)
 */

#ifndef PHC_SHREDDER_H
#define PHC_SHREDDER_H

#include "Lower_expr.h"

List<AST_statement*>* shred (List<AST_statement*>* in);
List<AST_statement*>* shred (AST_statement* in);

class Shredder : public Lower_expr
{
public:
	void children_php_script(AST_php_script* in);
	void post_nop(AST_nop* in);

public:
	AST_variable* post_variable(AST_variable* in);
	AST_expr* post_bin_op(AST_bin_op* in);
	AST_expr* post_unary_op(AST_unary_op* in);
	AST_expr* post_method_invocation(AST_method_invocation* in);
	AST_expr* post_int(Token_int* in);
	AST_expr* post_real(Token_real* in);
	AST_expr* post_bool(Token_bool* in);
	AST_expr* post_string(Token_string* in);
	AST_expr* post_null(Token_null* in);
	AST_expr* post_constant (AST_constant* in);
	AST_expr* post_array(AST_array* in);
	AST_expr* post_assignment(AST_assignment* in);
	void pre_eval_expr (AST_eval_expr* in, List<AST_statement*>* out);

};

#endif // PHC_SHREDDER_H
