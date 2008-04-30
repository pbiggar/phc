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

void Split_multiple_arguments::pre_global(Global* in, List<Statement*>* out)
{
	for_lci (in->variable_names, Variable_name, i)
	{
		Global* global = new Global(new List<Variable_name*>(*i));
		global->attrs = in->attrs->clone();
		out->push_back(global);
	}
}
	
void Split_multiple_arguments::pre_static_declaration(Static_declaration* in, List<Statement*>* out)
{
	for_lci (in->vars, Name_with_default, i)
	{
		Static_declaration* stat = new Static_declaration(new List<Name_with_default*>(*i));
		stat->attrs = in->attrs->clone();
		out->push_back(stat);
	}
}
	
void Split_multiple_arguments::pre_attribute(Attribute* in, List<Member*>* out)
{
	for_lci (in->vars, Name_with_default, i)
	{
		Attribute* attr = new Attribute(in->attr_mod->clone (), new List<Name_with_default*>(*i));
		attr->attrs = in->attrs->clone();
		out->push_back(attr);
	}
}
