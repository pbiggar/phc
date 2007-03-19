/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Modify 'target' attribute on variables in %MAIN%::%run%()
 */

#include "Variable_targets.h"

Variable_targets::Variable_targets() 
{
	in_run = false;
}

Variable_targets::~Variable_targets() 
{
}

void Variable_targets::pre_class_def(AST_class_def* in)
{
	current_class = in;
}

void Variable_targets::pre_method(AST_method* in)
{
	in_run = *in->signature->method_name->value == "%run%";
}

void Variable_targets::post_method(AST_method* in)
{
	if(in_run)
	{
		set<Token_variable_name*, ltstr>::const_iterator i;
		for(i = var_names.begin(); i != var_names.end(); i++)
		{
			AST_attribute* attr = new AST_attribute(AST_attr_mod::new_STATIC(), *i, NULL);
			current_class->members->push_back(attr);
		}
	}
}

void Variable_targets::pre_variable(AST_variable* in)
{
	if(in_run && !in->target)
	{
		in->target = new Token_class_name(new String("%MAIN%"));
		Token_variable_name* name = dynamic_cast<Token_variable_name*>(in->variable_name);
		if(name)
		{
			var_names.insert(name->clone());
		}
	}
}
