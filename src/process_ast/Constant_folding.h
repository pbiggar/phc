/* 
 * phc -- the open source PHP compiler 
 * See doc/license/README.license for licensing information
 *
 * Fold constant binary and unary expressions.
 * Note lack of constant propagation.
 */

#ifndef PHC_CONSTANT_FOLDING_H
#define PHC_CONSTANT_FOLDING_H

#include "AST_transform.h"

class Constant_folding : public AST::Transform, virtual public GC_obj
{
public:
	AST::Expr* post_bin_op(AST::Bin_op* in);
	AST::Expr* post_unary_op(AST::Unary_op* in);
};

#endif // PHC_CONSTANT_FOLDING_H
