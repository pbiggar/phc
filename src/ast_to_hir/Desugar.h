/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Reduce the amount of statement types needed by adding temporaries where
 * there were none before.
 */

#ifndef PHC_DESUGAR_H
#define PHC_DESUGAR_H

#include "AST_transform.h"

class Desugar : public AST::AST_transform
{
	void pre_eval_expr(AST::AST_eval_expr* in, List<AST::AST_statement*>* out);
	void pre_nop(AST::AST_nop*, List<AST::AST_statement*>*);
	AST::AST_expr* pre_unary_op(AST::AST_unary_op* in);
	void pre_return(AST::AST_return*, List<AST::AST_statement*>*);
	void pre_declare (AST::AST_declare*, List<AST::AST_statement*>*);
};

#endif // PHC_DESUGAR_H
