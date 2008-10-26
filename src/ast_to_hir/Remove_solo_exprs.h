/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Remove statements which are by themselves in the AST. Mostly, these
 * variables are created by the shredder.
 */

#ifndef PHC_REMOVE_SOLO_EXPRS_H
#define PHC_REMOVE_SOLO_EXPRS_H

#include "AST_transform.h"

class Remove_solo_exprs : public AST::Transform, virtual public GC_obj
{
	void post_eval_expr (AST::Eval_expr* in, AST::Statement_list* out)
	{
		if (isa<AST::Variable> (in->expr)
			|| in->expr->match (new AST::Method_invocation (
					NULL,
					new AST::METHOD_NAME ("isset"),
					new AST::Actual_parameter_list ( // isset is split already
						new AST::Wildcard<AST::Actual_parameter>))))
		{
			// Remove the solo expr
		}
		else
			out->push_back (in);
	}
};

#endif // PHC_REMOVE_SOLO_EXPRS_H
