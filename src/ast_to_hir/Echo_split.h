/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert echo()es to print()s
 */

#ifndef PHC_ECHO_SPLIT_H
#define PHC_ECHO_SPLIT_H

#include "AST_transform.h"

class Echo_split : public AST::AST_transform
{
	void pre_eval_expr(AST::AST_eval_expr* in, List<AST::AST_statement*>* out);
};



#endif // PHC_ECHO_SPLIT_H
