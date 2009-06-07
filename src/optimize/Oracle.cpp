/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Optimization oracle acts as a go-between for the Optimization passes and
 * Embed.
 */

#include "Oracle.h"
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
			phc_TODO ();

		else if (Class_def* c = dynamic_cast<Class_def*> (stmt))
			add_class_info (new User_class_info (c));
	}

	add_method_info (new Builtin_method_info (s("print")));
	add_method_info (new Builtin_method_info (s("die")));
	add_method_info (new Builtin_method_info (s("exit")));
	add_method_info (new Builtin_method_info (s("echo")));
	add_method_info (new Builtin_method_info (s("empty")));
}


/*
 * Methods
 */
Map<string, Method_info*> Oracle::methods;

Method_info*
Oracle::get_method_info (String* method_name)
{
	// Cached
	if (methods.has (*method_name))
		return methods [*method_name];

	// Lookup the embed SAPI
	Method_info* info = PHP::get_method_info (method_name);

	// Cache it
	if (info)
	{
		add_method_info (info);
		return get_method_info (method_name);
	}

	// require etc al have to be done.
	if (is_builtin_function (method_name))
		phc_TODO ();

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
	assert (!methods.has (*info->name));

	methods[*info->name] = info;
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

	return !info->is_side_effecting ();
}


/*
 * Classes
 */
Map<string, Class_info*> Oracle::classes;

void
Oracle::add_class_info (Class_info* info)
{
	assert (!classes.has (*info->name));

	classes[*info->name] = info;
}
