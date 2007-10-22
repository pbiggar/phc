/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Move isset and unset into individual calls.
 */

#ifndef PHC_SPLIT_UNSET_ISSET_H
#define PHC_SPLIT_UNSET_ISSET_H

#include "Lower_expr.h"
#include "fresh.h"
#include "process_ast/Invalid_check.h"

class Split_unset_isset : public AST_transform
{
public:
	// Split unset 
	void pre_eval_expr(AST_eval_expr* in, List<AST_statement*>* out);

	// Split isset
	AST_expr* pre_method_invocation(AST_method_invocation* in); 
};

#endif // PHC_SPLIT_UNSET_ISSET_H
