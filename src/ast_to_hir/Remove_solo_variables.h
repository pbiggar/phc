/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Remove statements which are by themselves in the AST. Mostly, these
 * variables are created by the shredder.
 */

#ifndef PHC_REMOVE_SOLO_VARIABLES_H
#define PHC_REMOVE_SOLO_VARIABLES_H

#include "AST_transform.h"

class Remove_solo_variables : public AST::Transform
{
	void post_eval_expr (AST::Eval_expr* in, AST::Statement_list* out)
	{
		if (isa<AST::Variable> (in->expr))
		{
			// Remove the solo variable
		}
		else
			out->push_back (in);
	}
};

#endif // PHC_REMOVE_SOLO_VARIABLES_H
