/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert print()s into to printf()s
 */

#ifndef PHC_TIDY_PRINT_H
#define PHC_TIDY_PRINT_H

#include "HIR_transform.h"
#include "process_ir/fresh.h"
#include "Shredder.h"


class Tidy_print : public HIR::Transform
{
	void pre_eval_expr (HIR::Eval_expr* in, List<HIR::Statement*>* out);
};

#endif // PHC_TIDY_PRINT_H
