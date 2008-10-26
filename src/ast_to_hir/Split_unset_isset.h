/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Move isset and unset into individual calls.
 */

#ifndef PHC_SPLIT_UNSET_ISSET_H
#define PHC_SPLIT_UNSET_ISSET_H

#include "AST_transform.h"

class Split_unset_isset : public AST::Transform, virtual public GC_obj
{
public:
	// Split unset 
	void pre_eval_expr(AST::Eval_expr* in, AST::Statement_list* out);

	// Split isset
	AST::Expr* pre_method_invocation(AST::Method_invocation* in); 
};

#endif // PHC_SPLIT_UNSET_ISSET_H
