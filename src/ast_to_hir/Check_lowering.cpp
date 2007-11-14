/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check that there are no nodes in the AST which should have been
 * lowered.
 */

#include "Check_lowering.h"

using namespace AST;

void Check_lowering::post_while(AST_while* in)
{
	assert (false);
}

void Check_lowering::post_do(AST_do* in)
{
	assert (false);
}

void Check_lowering::post_for(AST_for* in)
{
	assert (false);
}

void Check_lowering::post_foreach(AST_foreach* in)
{
	assert (false);
}

void Check_lowering::post_switch(AST_switch* in)
{
	assert (false);
}

void Check_lowering::post_if(AST_if* in)
{
	assert (false);
}

void Check_lowering::post_break(AST_break* in)
{
	assert (false);
}

void Check_lowering::post_continue(AST_continue* in)
{
	assert (false);
}

void Check_lowering::post_bin_op (AST_bin_op* in)
{
	if (*in->op->value == "||"
		|| *in->op->value == "or"
		|| *in->op->value == "&&"
		|| *in->op->value == "and"
		|| *in->op->value == ",")
		assert (false);
}


void Check_lowering::post_conditional_expr (AST_conditional_expr* in)
{
	assert (false);
}
