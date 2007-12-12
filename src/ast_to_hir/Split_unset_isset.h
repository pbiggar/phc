/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Move isset and unset into individual calls.
 */

#ifndef PHC_SPLIT_UNSET_ISSET_H
#define PHC_SPLIT_UNSET_ISSET_H

#include "hir_to_mir/HIR_lower_expr.h"
#include "HIR_transform.h"
#include "process_ir/fresh.h"

class Split_unset_isset : public HIR::Transform
{
public:
	// Split unset 
	void pre_eval_expr(HIR::Eval_expr* in, List<HIR::Statement*>* out);

	// Split isset
	HIR::Expr* pre_method_invocation(HIR::Method_invocation* in); 
};

#endif // PHC_SPLIT_UNSET_ISSET_H
