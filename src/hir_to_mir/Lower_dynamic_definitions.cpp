/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Move dynamic class definitions to the top-level, and replace them with
 * run-time aliases.
 */

#include "Lower_dynamic_definitions.h"
#include "process_ir/General.h"

using namespace HIR;

/* Convert
 *
 *		if ($x)
 *		{
 *			function y ()
 *			{
 *			}
 *		}
 *
 *	into
 *	
 *		function y__v1 ()
 *		{
 *		}
 *		if ($x)
 *		{
 *			alias ("y", "y__v1");
 *		}
 *
 *	This is only for functions, methods aren't affected since they must be
 *	declared in a class.
 *
 *	Classes cannot be nested (nor interfaces). However, functions may be defined
 *	within other functions or within Methods.
 */

void
Lower_dynamic_definitions::children_php_script (PHP_script* in)
{
	new_defs = new Statement_list;
	Transform::children_php_script (in);
	in->statements->push_back_all (new_defs);
}

void
Lower_dynamic_definitions::post_class_def (Class_def* in, Statement_list* out)
{
	// TODO the attribute is set much earlier. It should probably be renamed.
	if (in->attrs->is_true ("phc.lower_control_flow.top_level_declaration"))
	{
		out->push_back (in);
		return;
	}

	CLASS_NAME* name = in->class_name;
	CLASS_NAME* new_name = fresh_class_name (*name->value);
	in->class_name = new_name;
	in->attrs->set_true ("phc.lower_control_flow.top_level_declaration");

	new_defs->push_back (in);
	out->push_back (
		new FOREIGN (
			new MIR::Class_alias (
				new MIR::CLASS_NAME (name->value),
				new MIR::CLASS_NAME (new_name->value))));
}

void
Lower_dynamic_definitions::post_interface_def (Interface_def* in, Statement_list* out)
{
	// TODO the attribute is set much earlier. It should probably be renamed.
	if (in->attrs->is_true ("phc.lower_control_flow.top_level_declaration"))
	{
		out->push_back (in);
		return;
	}

	INTERFACE_NAME* name = in->interface_name;
	INTERFACE_NAME* new_name = fresh_interface_name (*name->value);
	in->interface_name = new_name;
	in->attrs->set_true ("phc.lower_control_flow.top_level_declaration");

	new_defs->push_back (in);
	out->push_back (
		new FOREIGN (
			new MIR::Interface_alias (
				new MIR::INTERFACE_NAME (name->value),
				new MIR::INTERFACE_NAME (new_name->value))));
}

// Functions can be nested anywhere. Only method and top-level declarations are
// not moved.
// post_statement isnt invoked for a Method (ie in a class), only for a function
// (ie anywhere else).
void
Lower_dynamic_definitions::post_statement (Statement* statement, Statement_list* out)
{
	// We cant use pre-method, because we can't push back a FOREIGN.
	if (not isa<Method> (statement))
	{
		Transform::post_statement (statement, out);
		return;
	}

	Method* in = dyc<Method> (statement);
	// TODO the attribute is set much earlier. It should probably be renamed.
	if (in->attrs->is_true ("phc.lower_control_flow.top_level_declaration"))
	{
		out->push_back (in);
		return;
	}

	METHOD_NAME* name = in->signature->method_name;
	METHOD_NAME* new_name = fresh_method_name (*name->value);
	in->signature->method_name = new_name;
	in->attrs->set_true ("phc.lower_control_flow.top_level_declaration");

	new_defs->push_back (in);
	out->push_back (
		new FOREIGN (
			new MIR::Method_alias (
				new MIR::METHOD_NAME (name->value),
				new MIR::METHOD_NAME (new_name->value))));
}
