/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Very simple inlining. Probably just removing calls to empty functions.
 */

#ifndef PHC_INLINING
#define PHC_INLINING

#include "Visit_once.h"

class Inlining : public Visit_once
{
public:
	void transform_eval_expr (Statement_block* in, MIR::Eval_expr*, BB_list* out);
};

#endif // PHC_INLINING
