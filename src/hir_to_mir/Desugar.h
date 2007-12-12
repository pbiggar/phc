/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Reduce the amount of statement types needed by adding temporaries where
 * there were none before.
 */

#ifndef PHC_DESUGAR_H
#define PHC_DESUGAR_H

#include "HIR_transform.h"

class Desugar : public HIR::Transform
{
	void pre_eval_expr(HIR::Eval_expr* in, List<HIR::Statement*>* out);
	void pre_nop(HIR::Nop*, List<HIR::Statement*>*);
	HIR::Expr* pre_unary_op(HIR::Unary_op* in);
	void pre_return(HIR::Return*, List<HIR::Statement*>*);
	void pre_declare (HIR::Declare*, List<HIR::Statement*>*);
};

#endif // PHC_DESUGAR_H
