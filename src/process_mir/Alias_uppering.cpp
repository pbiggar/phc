/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Upper method, class and function aliases.
 */

#include "Alias_uppering.h"
#include "parsing/Parse_buffer.h"

using namespace MIR;

void Alias_uppering::pre_class_alias (MIR::Class_alias* in, Statement_list* out)
{
	(*out
		<< "class " << in->alias << " extends " << in->class_name << "{}"
	).finish (in);
	out->front()->attrs->set_false ("phc.lower_control_flow.top_level_declaration");
}

void Alias_uppering::pre_interface_alias (MIR::Interface_alias* in, Statement_list* out)
{
	(*out
		<< "interface " << in->alias << " extends " << in->interface_name << "{}"
	).finish (in);
	out->front()->attrs->set_false ("phc.lower_control_flow.top_level_declaration");
}

void Alias_uppering::pre_method_alias (MIR::Method_alias* in, Statement_list* out)
{
	(*out
		<< "function " << in->alias << "()\n"
		<< "{\n"
		<< "	call_user_func_array (\"" << in->method_name << "\", func_get_args ());\n"
		<< "}\n"
	).finish (in);
	out->front()->attrs->set_false ("phc.lower_control_flow.top_level_declaration");
}
