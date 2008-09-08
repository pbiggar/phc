/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Remove all statements after the AST.
 */

#include "pass_manager/Plugin_pass.h"
#include "process_ir/General.h"

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	// defer until we know the option
	pm->add_before_named_pass (pass, s("ast"));
}

extern "C" void run_ast (AST::PHP_script* in, Pass_manager* pm, String* option)
{
	pm->remove_after_named_pass (option);
}
