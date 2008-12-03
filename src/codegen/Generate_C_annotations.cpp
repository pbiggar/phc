/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Annotate MIR for code generation.
 */

#include "Generate_C_annotations.h"

void
Generate_C_annotations::pre_method (MIR::Method* in)
{
	var_names.clear ();
}

void
Generate_C_annotations::post_method (MIR::Method* in)
{
	String_list* result = new String_list;

	// convert from string to String*
	foreach (string name, var_names)
		result->push_back (s (name));

	in->attrs->set ("phc.codegen.non_st_vars", result);
}

// TODO: this should get the signature too
void
Generate_C_annotations::post_variable_name (MIR::VARIABLE_NAME* in)
{
	if (in->attrs->is_true ("phc.codegen.st_entry_not_required"))
	{
		var_names.insert (*in->value);
	}
}
