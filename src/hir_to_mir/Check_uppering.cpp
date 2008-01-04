/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check there are no gotos or labels left.
 */

#include "Check_uppering.h"

using namespace AST;

void Check_uppering::post_goto (Goto* in)
{
	assert (false);
}

void Check_uppering::post_label (Label* in)
{
	assert (false);
}

void Check_uppering::post_continue (Continue* in)
{
	// these are allowed again, since we add them
}

void Check_uppering::post_switch (Switch* in)
{
	// these are allowed again, since we add them
}

void Check_uppering::post_if (If* in)
{
	// these are allowed again, since we add them
}

void Check_uppering::post_break (Break* in)
{
	if (not in->match (new Break (new INT (2))))
	{
		phc_internal_error ("The single break should jump two levels", in);
	}
}

void Check_uppering::post_while (While* in)
{
	if (not in->match (new While (new BOOL (true), NULL)))
	{
		phc_internal_error ("The single while should be while true", in);
	}
}
