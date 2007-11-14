/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Reduce the amount of statement types needed by adding temporaries where
 * there were none before.
 */

#ifndef PHC_DESUGAR_H
#define PHC_DESUGAR_H

#include "Lower_expr.h"
#include "fresh.h"
#include "process_ast/Invalid_check.h"


class Desugar : public AST::AST_transform
{
	void pre_eval_expr(AST::AST_eval_expr* in, List<AST::AST_statement*>* out);
	void pre_nop(AST::AST_nop* in, List<AST::AST_statement*>* out);
	AST::AST_expr* pre_unary_op(AST::AST_unary_op* in);
	void pre_return(AST::AST_return* in, List<AST::AST_statement*>* out);
};

#endif // PHC_DESUGAR_H
