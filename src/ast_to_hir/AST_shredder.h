/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * shredder (n.): a machine that tears objects into smaller pieces.
 * (Transform the AST into 3AC-like code)
 */

#ifndef PHC_SHREDDER_H
#define PHC_SHREDDER_H

#include "ast_to_hir/AST_lower_expr.h"

class Shredder : public AST::Lower_expr
{
public:
	void children_php_script(AST::PHP_script* in);
	void post_nop(AST::Nop* in);

public:
	AST::Variable* post_variable(AST::Variable* in);
	AST::Expr* post_new (AST::New* in);
	AST::Expr* post_bin_op(AST::Bin_op* in);
	AST::Expr* post_unary_op(AST::Unary_op* in);
	AST::Expr* post_cast(AST::Cast* in);
	AST::Expr* post_instanceof(AST::Instanceof* in);
	AST::Expr* post_method_invocation(AST::Method_invocation* in);
	AST::Expr* post_int(AST::INT* in);
	AST::Expr* post_real(AST::REAL* in);
	AST::Expr* post_bool(AST::BOOL* in);
	AST::Expr* post_string(AST::STRING* in);
	AST::Expr* post_nil(AST::NIL* in);
	AST::Expr* post_constant (AST::Constant* in);
	AST::Expr* post_array(AST::Array* in);
	AST::Expr* post_assignment(AST::Assignment* in);
	AST::Expr* post_op_assignment(AST::Op_assignment* in);
	AST::Expr* pre_ignore_errors(AST::Ignore_errors* in);
	AST::Expr* post_ignore_errors(AST::Ignore_errors* in);
};


#endif // PHC_SHREDDER_H
