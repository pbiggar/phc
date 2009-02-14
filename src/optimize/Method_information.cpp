/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Try to model functions as accurately as possible.
 */

#include "Method_information.h"
#include "MIR.h"

using namespace MIR;

Method_info::Method_info (String* name)
: name (name)
{
}


/*
 * User methods -- Internal methods are defined in optimize.cpp
 */

User_method_info::User_method_info (Method* method)
: Method_info (method->signature->method_name->value)
, method (method)
, cfg (NULL)
, side_effecting (false)
{
}

bool
User_method_info::has_implementation ()
{
	return true;
}

bool
User_method_info::return_by_ref ()
{
	return method->signature->return_by_ref;
}

bool
User_method_info::param_by_ref (int param_index)
{
	if ((unsigned int)(param_index+1)
			> method->signature->formal_parameters->size())
	{
		// TODO: remove pass_rest_by_ref
		return false;
	}
	else
	{
		return method->signature->formal_parameters->at (param_index)->is_ref;
	}
}

VARIABLE_NAME*
User_method_info::param_name (int param_index)
{
	if ((unsigned int)(param_index+1)
			> method->signature->formal_parameters->size())
	{
		return unnamed_param (param_index);
	}
	else
	{
		return method->signature->formal_parameters->at (
			param_index)->var->variable_name;
	}
}

Static_value*
User_method_info::default_param (int param_index)
{
	if ((unsigned int)(param_index+1) 
			> method->signature->formal_parameters->size())
		return NULL;
	else
	{
		return method->signature->formal_parameters->at (
			param_index)->var->default_value;
	}
}

bool
User_method_info::is_side_effecting ()
{
	return side_effecting;
}


VARIABLE_NAME*
unnamed_param (int param_index)
{
	stringstream ss;
	ss << "__UNNAMED__" << param_index;
	return new VARIABLE_NAME (s(ss.str()));
}
