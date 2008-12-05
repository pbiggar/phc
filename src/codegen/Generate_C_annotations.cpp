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

/*
 * Whole script analysis
 */

void
Generate_C_annotations::pre_php_script (PHP_script* in)
{
	pool_values.clear ();
}

void
Generate_C_annotations::post_php_script (PHP_script* in)
{
	// Add a list of literal-pooled variables to the script.
	IR::Node_list* program_literals = new IR::Node_list;

	int ids[] = { MIR::STRING::ID, INT::ID, REAL::ID, MIR::BOOL::ID, NIL::ID };
	foreach (int id, ids)
		program_literals->push_back_all (
			rewrap_list <MIR::Literal, IR::Node> (pool_values[id].values ()));

	in->attrs->set ("phc.codegen.pooled_literals", program_literals);
}

void
Generate_C_annotations::post_literal (Literal* in)
{
	// Annotate each literal with a name for its pooled variable. Separate
	// pools for each class
	string index = *in->get_value_as_string ();
	Map<string, Literal*>& pool = pool_values [in->classid ()];

	if (!pool.has (index))
	{
		// dont use the value as the suffix, as string values can be very long
		stringstream ss;
		ss << "literal_pool_" << in->classid () << "_" << pool.size ();
		in->attrs->set ("phc.codegen.pool_name", s (ss.str ()));
		pool [index] = in;
	}

	in->attrs->set (
		"phc.codegen.pool_name", 
		pool [index]->attrs->get_string ("phc.codegen.pool_name")->clone ());

}



/*
 * Method analysis
 */

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
