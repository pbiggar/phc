/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert print()s into to printf()s
 */

#ifndef PHC_TIDY_PRINT_H
#define PHC_TIDY_PRINT_H

#include "AST_transform.h"


class Tidy_print : public AST::Transform
{
	void pre_eval_expr (AST::Eval_expr* in, AST::Statement_list* out);
};

#endif // PHC_TIDY_PRINT_H
