/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Try to model functions as accurately as possible.
 */

#include "MIR.h"

#include "Class_info.h"
#include "Method_info.h"

using namespace MIR;

Class_info::Class_info (String* name)
: name (name)
{
}


/*
 * User methods -- Internal methods are defined in optimize.cpp
 */

User_class_info::User_class_info (Class_def* class_def)
: Class_info (class_def->class_name->value)
, class_def (class_def)
{
	foreach (Member* member, *class_def->members)
	{
		if (Method* method = dynamic_cast<Method*> (member))
		{
			this->methods[*method->signature->method_name->value] = new User_method_info (method);
		}
		else
			// We havent assigned fields anywhere.
			phc_TODO ();
	}
}

bool
User_class_info::has_implementation ()
{
	return true;
}

Method_info*
User_class_info::get_method_info (String* name, bool search)
{
	// TODO: look at inheritence hierarchy and interfaces.
	if (not this->methods.has (*name))
	{
		if (search)
			phc_TODO ();
		else
			return NULL;
	}

	return methods [*name];
}


/*
 * Summary methods
 */

Summary_class_info::Summary_class_info (String* name)
: Class_info (name)
{
}


/*
 * Builtins
 */


Builtin_class_info::Builtin_class_info (String* name)
: Summary_class_info (name)
{
}


bool
Builtin_class_info::has_implementation ()
{
	return false;
}

