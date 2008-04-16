/* 
 * phc -- the open source PHP compiler 
 * See doc/license/README.license for licensing information
 *
 * Fold constant binary and unary expressions.
 * Note lack of constant propagation.
 */

#ifndef PHC_CONSTANT_FOLDING
#define PHC_CONSTANT_FOLDING

#include "AST_transform.h"


class Constant_folding : public AST::Transform
{
public:
	AST::Expr* post_bin_op(AST::Bin_op* in);
	AST::Expr* post_unary_op(AST::Unary_op* in);
};

#endif // PHC_CONSTANT_FOLDING
