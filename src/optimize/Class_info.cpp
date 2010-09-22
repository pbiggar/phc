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
, parent (NULL)
{
	this->lc_name = name->to_lower ();
}

Method_info_list*
Class_info::get_methods ()
{
	Method_info_list* result = new Method_info_list ();
	
	string s;
	Method_info* m;
	foreach (tie (s, m), methods)
		result->push_back (m);

	return result;
}

Method_info*
Class_info::get_method_info (String* method_name, bool search)
{
	String* mname = method_name->to_lower ();

	if (not this->methods.has (*mname))
	{
		if (search)
		{
			// TODO: Look up interfaces

			// Look up inheritence hierarchy
			Class_info* parent = this->get_parent ();
			if (parent == NULL)
				return NULL;

			return parent->get_method_info (mname, search);
		}
		else
			return NULL;
	}

	return methods [*mname];
}

Class_info*
Class_info::get_parent ()
{
	return parent;
}

void
Class_info::set_parent (Class_info* parent)
{
	assert (this->parent == NULL);
	this->parent = parent;
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
			String* name = method->signature->method_name->value->to_lower ();

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
				|| *name == "__unset"
				|| *name == "__wakeup"
				)
			{
        stringstream ss;
        ss << "Magic method '" << *name << " is not supported";
        phc_optimization_exception (ss.str());
			}

			User_method_info* umi = new User_method_info (this, method);
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
  phc_optimization_exception ("Built-in classes are not supported");
}
