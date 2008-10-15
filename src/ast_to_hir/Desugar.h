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

class Desugar : public AST::Transform, virtual public GC_obj
{
	void pre_nop(AST::Nop*, AST::Statement_list*);
	AST::Expr* pre_unary_op(AST::Unary_op* in);
	void pre_return(AST::Return*, AST::Statement_list*);
	void pre_declare (AST::Declare*, AST::Statement_list*);
};

#endif // PHC_DESUGAR_H
