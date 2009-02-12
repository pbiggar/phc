/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Try to model functions as accurately as possible.
 */

#include "Method_information.h"
#include "MIR.h"


bool
Method_info::has_implementation ()
{
	return implementation != NULL;
}


bool
Method_info::has_parameters ()
{
	if (implementation)
		return implementation->signature->formal_parameters->size () != 0;
	else
		return params->size () != 0;
}

Parameter_info*
Method_info::param_at (int index)
{
	int i = 0;
	foreach (Parameter_info* param, *params)
	{
		if (i == index)
			return param;
	}
	assert (params->back()->use_for_rest);
	return params->back ();
}

void
Method_info::add_param (Parameter_info* param)
{
	params->push_back (param);
}
