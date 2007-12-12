/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert echo()es to print()s
 */

#ifndef PHC_ECHO_SPLIT_H
#define PHC_ECHO_SPLIT_H

#include "HIR_transform.h"

class Echo_split : public HIR::Transform
{
	void pre_eval_expr(HIR::Eval_expr* in, List<HIR::Statement*>* out);
};



#endif // PHC_ECHO_SPLIT_H
