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
