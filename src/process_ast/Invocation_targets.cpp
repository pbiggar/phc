/* 
 * phc -- the open source PHP compiler 
 * See doc/license/README.license for licensing information
 *
 * Modify 'target' attribute on method invocations 
 * 
 * If the user does not specify a target for a method invocation, the parser
 * will set the corresponding field to NULL. However, target is not an optional
 * field; this transform will fix this. For methods defined in %MAIN%, target
 * will be set to %MAIN%. For other methods, target will be set to %STDLIB%.
 * Thus, if there is a name clash between a user-defined method and one in the
 * PHP library, we assume it is the users method that is called.
 *
 * The transform consists of two separate visitors: 
 *
 * Collect_method_names collects all method names that are defined in %MAIN%.
 * This visitor does not need to be called explicitely (it is called from
 * Invocation_targets)
 *
 * Invocation_targets then sets the 'target' attribute as described above.
 */

#include "Invocation_targets.h" 

Collect_method_names::Collect_method_names() 
{
	in_main = false;
}

Collect_method_names::~Collect_method_names() 
{
}

void Collect_method_names::pre_class_def(AST_class_def* in)
{
	in_main = *in->class_name->value == "%MAIN%";
}

void Collect_method_names::pre_signature(AST_signature* in)
{
	if(in_main)
		method_names.push_back(in->method_name);
}

void Collect_method_names::children_method_invocation(AST_method_invocation* in)
{
	// We avoid traversing the children of a method invocation
	// (because target has not yet been set)
}

Invocation_targets::Invocation_targets() 
{
}

Invocation_targets::~Invocation_targets() 
{
}

void Invocation_targets::pre_php_script(AST_php_script* in)
{
	in->visit(&cmn);
}

void Invocation_targets::pre_method_invocation(AST_method_invocation* in)
{
	if(in->target == NULL)
	{
		// TODO: Deal with reflection (impossible :-)
		Token_method_name* name = dynamic_cast<Token_method_name*>(in->method_name);
		if(name && defined_in_main(name))
			in->target = new Token_class_name(new String("%MAIN%"));
		else
			in->target = new Token_class_name(new String("%STDLIB%"));
	}
}

bool Invocation_targets::defined_in_main(Token_method_name* name)
{
	List<Token_method_name*>::const_iterator i;
	for(i = cmn.method_names.begin(); i != cmn.method_names.end(); i++)
	{
		if(*((*i)->value) == *name->value)
		{
			return true;
		}
	}
	return false;
}
