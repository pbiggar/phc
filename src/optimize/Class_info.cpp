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

Method_info*
Class_info::get_method_info (String* name, bool search)
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
			String* name = method->signature->method_name->value;
			if (false 
				|| *name == "__call"
				|| *name == "__callStatic"
				|| *name == "__clone"
				|| *name == "__destruct"
				|| *name == "__get"
				|| *name == "__invoke"
				|| *name == "__isset"
				|| *name == "__set"
				|| *name == "__set_state"
				|| *name == "__sleep"
				|| *name == "__toString"
				|| *name == "__unset"
				|| *name == "__wakeup"
				)
			{
				phc_TODO ();
			}

			User_method_info* umi = new User_method_info (this, method);
			umi->add_self_parameter ();

			this->methods[*name] = umi;
		}
	}
}

Attribute_list*
User_class_info::get_attributes ()
{
	return filter_types <Attribute> (class_def->members);
}



/*
 * Summary methods
 */

Summary_class_info::Summary_class_info (String* name)
: Class_info (name)
{
	phc_TODO ();
}
