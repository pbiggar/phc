/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Optimization oracle acts as a go-between for the Optimization passes and
 * Embed.
 */

#include "Oracle.h"
#include "Abstract_value.h"
#include "embed/embed.h"
#include "process_ir/General.h"

using namespace MIR;
using namespace boost;

// TODO: We dont put Method_mods into the signature.
void
Oracle::initialize (MIR::PHP_script* in)
{
	/*
	 * Add existing functions
	 */
	foreach (Statement* stmt, *in->statements)
	{
		if (Method* m = dynamic_cast<Method*> (stmt))
			add_method_info (new User_method_info (m));

		else if (Interface_def* i = dynamic_cast<Interface_def*> (stmt))
	    phc_optimization_exception("Interfaces are not supported");

		else if (Class_def* c = dynamic_cast<Class_def*> (stmt))
			add_class_info (new User_class_info (c));
	}

	add_method_info (new Builtin_method_info (s("print")));
	add_method_info (new Builtin_method_info (s("die")));
	add_method_info (new Builtin_method_info (s("exit")));
	add_method_info (new Builtin_method_info (s("echo")));
	add_method_info (new Builtin_method_info (s("empty")));

	// We can't invoke on these types, but they do exist, and we might try to
	// invoke on them because of meet-over-all-paths.
	foreach (string type, *Type_info::get_all_scalar_types ())
	{
		Oracle::classes[type] = NULL;
	}
	Oracle::classes["array"] = NULL;

	/*
	 * Update parents
	 */

	foreach (User_class_info* info, *filter_types <User_class_info> (Oracle::get_all_classes ()))
	{
		if (info->class_def->extends)
		{
			info->set_parent (Oracle::get_class_info (info->class_def->extends->value));
		}
	}

	// TODO: we need classes for builtin types
}


/*
 * Methods
 */

Map<string, Method_info*> Oracle::methods;

Method_info*
Oracle::get_method_info (String* method_name)
{
	String* name = method_name->to_lower ();

	// Cached
	if (methods.has (*name))
		return methods [*name];

	// Lookup the embed SAPI
	Method_info* info = PHP::get_method_info (name);

	// Cache it
	if (info)
	{
		add_method_info (info);
		return get_method_info (name);
	}

	// require etc al have to be done.
	if (is_builtin_function (name))
	{
		stringstream ss;
		ss << "Builtin function \"" << *name << "\" is not modelled" << endl;
	  phc_optimization_exception (ss.str()) ;
	}

	return NULL;
}

User_method_info*
Oracle::get_user_method_info (String* method_name)
{
	return dynamic_cast<User_method_info*> (get_method_info (method_name));
}

void
Oracle::add_method_info (Method_info* info)
{
	assert (!methods.has (*info->lc_name));

	methods[*info->lc_name] = info;
}

void
Oracle::add_method_alias (String* original, String* alias)
{
	Method_info* info = get_method_info (original->to_lower ());

	methods[*alias] = info;
}

Method_info_list*
Oracle::get_all_methods ()
{
	return methods.values ();
}

bool
Oracle::is_pure_function (MIR::METHOD_NAME* name)
{
	Method_info* info = get_method_info (name->value);
	if (info == NULL)
		return false;

	// Special case for constant functions.
	// These functions can be removed by dce.
	if (*info->name == "defined")
		return true;
	else
		return not info->get_side_effecting ();
}


/*
 * Classes
 */
Map<string, Class_info*> Oracle::classes;

void
Oracle::add_class_info (Class_info* info)
{
	assert (!classes.has (*info->lc_name));

	classes[*info->lc_name] = info;
}

void
Oracle::add_class_alias (String* original, String* alias)
{
	Class_info* info = get_class_info (original->to_lower ());

	classes[*alias] = info;
}

Class_info*
Oracle::get_class_info (String* class_name)
{
	String* name = class_name->to_lower ();

	if (not classes.has (*name))
	{
		stringstream ss;
		ss << "Class \"" << *name << "\" not found" << endl;
	  phc_optimization_exception (ss.str()) ;
	}

	return classes[*name];
}

Class_info_list*
Oracle::get_all_classes ()
{
	return classes.values ();
}

User_class_info*
Oracle::get_user_class_info (String* name)
{
	return dynamic_cast<User_class_info*> (get_class_info (name));
}
