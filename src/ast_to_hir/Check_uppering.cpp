/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check there are no gotos or labels left.
 */

#include "Check_uppering.h"

void Check_uppering::post_goto (AST_goto* in)
{
	assert (false);
}

void Check_uppering::post_label (AST_label* in)
{
	assert (false);
}

void Check_uppering::post_continue (AST_continue* in)
{
	// these are allowed again, since we add them
}

void Check_uppering::post_switch (AST_switch* in)
{
	// these are allowed again, since we add them
}

void Check_uppering::post_if (AST_if* in)
{
	// these are allowed again, since we add them
}

void Check_uppering::post_break (AST_break* in)
{
	if (not in->match (new AST_break (new Token_int (2, NULL))))
	{
		phc_internal_error ("The single break should jump two levels", in);
	}
}

void Check_uppering::post_while (AST_while* in)
{
	if (not in->match (new AST_while (new Token_bool (true, NULL), NULL)))
	{
		phc_internal_error ("The single while should be while true", in);
	}
}
