/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Annotate MIR for code generation.
 */

#include "Generate_C_annotations.h"
#include <sstream>

#include "cmdline.h"
extern struct gengetopt_args_info args_info;

using namespace MIR;
using namespace std;

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
	compiled_functions.push(new Signature_list);
}

void
Generate_C_annotations::post_php_script (PHP_script* in)
{
	// Add a list of literal-pooled variables to the script.
	Literal_list* program_literals = new Literal_list;

	int ids[] = { MIR::STRING::ID, INT::ID, REAL::ID, MIR::BOOL::ID, NIL::ID };
	foreach (int id, ids)
		program_literals->push_back_all (pool_values[id].values ());

	in->attrs->set_list ("phc.codegen.pooled_literals", program_literals);


	// Add a list of methods called.
	String_list* method_names = new String_list;
	foreach (string name, cached_functions)
		method_names->push_back (s (name));

	in->attrs->set ("phc.codegen.cached_functions", method_names);


	// Get a list of compiled functions
  Signature_list* cf;
	cf = compiled_functions.top(); compiled_functions.pop();
	assert(compiled_functions.empty());
	in->attrs->set_list ("phc.codegen.compiled_functions", cf);
}

void
Generate_C_annotations::post_literal (Literal* in)
{
	if (!args_info.optimize_given)
		return;

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

void
Generate_C_annotations::post_param_is_ref (Param_is_ref* in)
{
	if (METHOD_NAME* method_name = dynamic_cast<METHOD_NAME*> (in->method_name))
		cached_functions.insert (*method_name->value);
}

void
Generate_C_annotations::post_method_invocation (Method_invocation* in)
{
	if (METHOD_NAME* method_name = dynamic_cast<METHOD_NAME*> (in->method_name))
	{
		CLASS_NAME* class_name = dynamic_cast<CLASS_NAME*>(in->target);

		if (in->target == NULL)
			cached_functions.insert (*method_name->value);
		else if (class_name != NULL)
		{
			stringstream fqn;
			fqn << *class_name->value << "_" << *method_name->value;
			cached_functions.insert (fqn.str());
		}
		else
		{
			// The function is part of an object; we cannot cache it 
		}
	}
}


/*
 * Method analysis
 */

void
Generate_C_annotations::pre_method (MIR::Method* in)
{
	var_names.clear ();
	iterators.clear ();

	if(!class_name.empty())
		in->signature->attrs->set ("phc.codegen.class_name", class_name.top()->clone());
	(compiled_functions.top())->push_back (in->signature->clone ());
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

// Should the return be returned by reference.
void
Generate_C_annotations::post_return (Return* in)
{
	// The signature at the back is this function.
	in->attrs->set ("phc.codegen.return_by_ref",
		new Boolean (
			(compiled_functions.top())->back ()->return_by_ref));
}

// Make sure phc.codegen.compiled_functions gets added to the class
// definition rather than the PHP script
void
Generate_C_annotations::pre_class_def(Class_def* in)
{
	compiled_functions.push(new Signature_list);
	class_name.push(in->class_name->value);
}

void
Generate_C_annotations::post_class_def(Class_def* in)
{
  Signature_list* cf;
	cf = compiled_functions.top(); compiled_functions.pop();
	in->attrs->set_list ("phc.codegen.compiled_functions", cf);
	class_name.pop();
}
