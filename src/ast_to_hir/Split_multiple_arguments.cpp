/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Split statements that accept multiple arguments in the AST but only a
 * single argument in the HIR (such as global, const, static and var) into
 * multiple statements, one for each argument in the source
 */

#include "Split_multiple_arguments.h"
#include "process_ir/General.h"

using namespace AST;

void Split_multiple_arguments::pre_global(Global* in, Statement_list* out)
{
	foreach (Variable_name* vn, *in->variable_names)
	{
		Global* global = new Global(new Variable_name_list(vn));
		global->attrs = in->attrs->clone();
		out->push_back(global);
	}
}
	
void Split_multiple_arguments::pre_static_declaration(Static_declaration* in, Statement_list* out)
{
	foreach (Name_with_default* nwd, *in->vars)
	{
		Static_declaration* stat = new Static_declaration(new Name_with_default_list(nwd));
		stat->attrs = in->attrs->clone();
		out->push_back(stat);
	}
}
	
void Split_multiple_arguments::pre_attribute(Attribute* in, Member_list* out)
{
	foreach (Name_with_default* nwd, *in->vars)
	{
		Attribute* attr = new Attribute(in->attr_mod->clone (), new Name_with_default_list(nwd));
		attr->attrs = in->attrs->clone();
		out->push_back(attr);
	}
}
