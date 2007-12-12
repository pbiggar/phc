/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Remove all statements after the AST.
 */

#include "pass_manager/Plugin_pass.h"

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->remove_after_named_pass ("ast");
}
