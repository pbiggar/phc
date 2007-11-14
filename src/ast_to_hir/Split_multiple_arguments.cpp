/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Split statements that accept multiple arguments in the AST but only a
 * single argument in the HIR (such as global, const, static and var) into
 * multiple statements, one for each argument in the source
 */

#include "Split_multiple_arguments.h"

using namespace AST;

void Split_multiple_arguments::pre_global(AST_global* in, List<AST_statement*>* out)
{
	List<AST_variable_name*>::const_iterator i;
	for(i = in->variable_names->begin(); i != in->variable_names->end(); i++)
	{
		AST_global* global = new AST_global(new List<AST_variable_name*>(*i));
		global->attrs = in->attrs->clone();
		out->push_back(global);
	}
}
	
void Split_multiple_arguments::pre_static_declaration(AST_static_declaration* in, List<AST_statement*>* out)
{
	List<AST_name_with_default*>::const_iterator i;
	for(i = in->vars->begin(); i != in->vars->end(); i++)
	{
		AST_static_declaration* stat = new AST_static_declaration(new List<AST_name_with_default*>(*i));
		stat->attrs = in->attrs->clone();
		out->push_back(stat);
	}
}
	
void Split_multiple_arguments::pre_attribute(AST_attribute* in, List<AST_member*>* out)
{
	List<AST_name_with_default*>::const_iterator i;
	for(i = in->vars->begin(); i != in->vars->end(); i++)
	{
		AST_attribute* attr = new AST_attribute(in->attr_mod, new List<AST_name_with_default*>(*i));
		attr->attrs = in->attrs->clone();
		out->push_back(attr);
	}
}
