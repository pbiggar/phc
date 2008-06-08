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

class Desugar : public AST::Transform
{
	void pre_nop(AST::Nop*, List<AST::Statement*>*);
	AST::Expr* pre_unary_op(AST::Unary_op* in);
	void pre_return(AST::Return*, List<AST::Statement*>*);
	void pre_declare (AST::Declare*, List<AST::Statement*>*);
};

#endif // PHC_DESUGAR_H
