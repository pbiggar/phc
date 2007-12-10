/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check that there are no nodes in the AST which should have been
 * lowered.
 */

#include "Check_lowering.h"

using namespace AST;

void Check_lowering::post_while(While* in)
{
	assert (false);
}

void Check_lowering::post_do(Do* in)
{
	assert (false);
}

void Check_lowering::post_for(For* in)
{
	assert (false);
}

void Check_lowering::post_foreach(Foreach* in)
{
	assert (false);
}

void Check_lowering::post_switch(Switch* in)
{
	assert (false);
}

void Check_lowering::post_if(If* in)
{
	assert (false);
}

void Check_lowering::post_break(Break* in)
{
	assert (false);
}

void Check_lowering::post_continue(Continue* in)
{
	assert (false);
}

void Check_lowering::post_bin_op (Bin_op* in)
{
	if (*in->op->value == "||"
		|| *in->op->value == "or"
		|| *in->op->value == "&&"
		|| *in->op->value == "and"
		|| *in->op->value == ",")
		assert (false);
}


void Check_lowering::post_conditional_expr (Conditional_expr* in)
{
	assert (false);
}
