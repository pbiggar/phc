/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Remove statements which are by themselves in the AST. Mostly, these
 * variables are created by the shredder.
 */

#ifndef PHC_REMOVE_SOLO_VARIABLES_H
#define PHC_REMOVE_SOLO_VARIABLES_H


#include "process_ir/General.h"

using namespace AST;

class Remove_solo_variables : public Transform
{
	void post_eval_expr (Eval_expr* in, List<Statement*>* out)
	{
		Variable* var = dynamic_cast<Variable*> (in->expr);
		if (var == NULL)
			out->push_back (in);
		else
		{
			// Remove the solo variable
		}
	}
};

#endif // PHC_REMOVE_SOLO_VARIABLES_H
