/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Make implicit parts of a script explicit for the Code Generator.
 */

#include "Clarify.h"
#include "process_ir/General.h"
#include "embed/embed.h"

using namespace MIR;

void Clarify::post_method (MIR::Method* in)
{
	// abstract method
	if (in->statements == NULL)
		return;

	// Not required for main. We're using the global symbol table.
	if (*in->signature->method_name->value == "__MAIN__")
		return;

	foreach (VARIABLE_NAME* var_name, *PHP::get_superglobals())
	{
		Global* glob = new Global (var_name);
		glob->attrs->set_true ("phc.optimize.is_super_global");
		in->statements->push_front (glob);
	}
}
