/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * shredder (n.): a machine that tears objects into smaller pieces.
 * (Transform the AST into 3AC-like code)
 */

#ifndef PHC_SHREDDER_H
#define PHC_SHREDDER_H

#include "AST.h"
#include "Lower_expr.h"

List<AST::AST_statement*>* shred (AST::AST_statement* in);

class Shredder : public Lower_expr
{
public:
	void children_php_script(AST::AST_php_script* in);
	void post_nop(AST::AST_nop* in);

public:
	AST::AST_variable* post_variable(AST::AST_variable* in);
	AST::AST_expr* post_bin_op(AST::AST_bin_op* in);
	AST::AST_expr* post_unary_op(AST::AST_unary_op* in);
	AST::AST_expr* post_cast(AST::AST_cast* in);
	AST::AST_expr* post_method_invocation(AST::AST_method_invocation* in);
	AST::AST_expr* post_int(AST::Token_int* in);
	AST::AST_expr* post_real(AST::Token_real* in);
	AST::AST_expr* post_bool(AST::Token_bool* in);
	AST::AST_expr* post_string(AST::Token_string* in);
	AST::AST_expr* post_null(AST::Token_null* in);
	AST::AST_expr* post_constant (AST::AST_constant* in);
	AST::AST_expr* post_array(AST::AST_array* in);
	AST::AST_expr* post_assignment(AST::AST_assignment* in);
	AST::AST_expr* post_op_assignment(AST::AST_op_assignment* in);
	AST::AST_expr* pre_ignore_errors(AST::AST_ignore_errors* in);
	AST::AST_expr* post_ignore_errors(AST::AST_ignore_errors* in);
	void pre_eval_expr (AST::AST_eval_expr* in, List<AST::AST_statement*>* out);
};


#endif // PHC_SHREDDER_H
