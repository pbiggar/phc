/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Annotate MIR for code generation.
 */

#include "Generate_C_annotations.h"

using namespace MIR;

// convert from string to String*
String_list* wrap_strings (Set<string>& set)
{
	String_list* result = new String_list;

	foreach (string name, set)
		result->push_back (s (name));

	return result;
}

void
Generate_C_annotations::pre_method (MIR::Method* in)
{
	var_names.clear ();
	iterators.clear ();
}

void
Generate_C_annotations::post_method (MIR::Method* in)
{
	in->attrs->set ("phc.codegen.non_st_vars", wrap_strings (var_names));
	in->attrs->set ("phc.codegen.ht_iterators", wrap_strings (iterators));
}


// Get the list of variables which dont need a symbol-table entry
void
Generate_C_annotations::post_variable_name (MIR::VARIABLE_NAME* in)
{
	if (in->attrs->is_true ("phc.codegen.st_entry_not_required"))
	{
		var_names.insert (*in->value);
	}
}

// Get the list of Hashtable iterators required.
void
Generate_C_annotations::post_ht_iterator (HT_ITERATOR* in)
{
	iterators.insert (*in->value);
}
