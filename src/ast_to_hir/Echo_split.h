/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert echo()es to print()s
 */

#ifndef PHC_ECHO_SPLIT_H
#define PHC_ECHO_SPLIT_H

#include "AST_transform.h"

class Echo_split : public AST::Transform, virtual public GC_obj
{
	void pre_eval_expr(AST::Eval_expr* in, AST::Statement_list* out);
};

#endif // PHC_ECHO_SPLIT_H
