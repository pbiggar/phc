/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Try to model functions as accurately as possible.
 */

#include "Method_information.h"
#include "MIR.h"

Method_info::Method_info (String* name)
: name (name)
{
}


/*
 * User methods -- Internal methods are defined in optimize.cpp
 */

User_method_info::User_method_info (MIR::Method* method)
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
User_method_info::param_by_ref (int param_index)
{
	if ((unsigned int)(param_index) > method->signature->formal_parameters->size() + 1)
		return method->signature->pass_rest_by_ref;
	else
		return method->signature->formal_parameters->at (param_index)->is_ref;
}

bool
User_method_info::return_by_ref ()
{
	return method->signature->return_by_ref;
}

bool
User_method_info::is_side_effecting ()
{
	return side_effecting;
}
