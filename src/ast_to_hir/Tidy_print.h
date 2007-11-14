/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert print()s into to printf()s
 */

#ifndef PHC_TIDY_PRINT_H
#define PHC_TIDY_PRINT_H

#include "AST_transform.h"
#include "fresh.h"
#include "Shredder.h"


class Tidy_print : public AST::AST_transform
{
	void pre_eval_expr (AST::AST_eval_expr* in, List<AST::AST_statement*>* out);
};

#endif // PHC_TIDY_PRINT_H
