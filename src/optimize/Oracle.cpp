/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Optimization oracle acts as a go-between for the Optimization passes and
 * Embed.
 */

#include "Oracle.h"
#include "embed/embed.h"

using namespace MIR;
using namespace boost;

Map<string, Method_info*> Oracle::infos;

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
			phc_TODO ();
	}

	add_method_info (new Builtin_method_info (s("print")));
}

Method_info*
Oracle::get_method_info (String* method_name)
{
	// Cached
	if (Oracle::infos.has (*method_name))
		return Oracle::infos [*method_name];

	// Lookup the embed SAPI
	Method_info* info = PHP::get_method_info (method_name);

	// Cache it
	if (info)
	{
		add_method_info (info);
		return get_method_info (method_name);
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
	assert (!infos.has (*info->name));

	infos[*info->name] = info;
}

Method_info_list*
Oracle::get_all_methods ()
{
	return infos.values ();
}

bool
Oracle::is_pure_function (MIR::METHOD_NAME* name)
{
	Method_info* info = get_method_info (name->value);
	if (info == NULL)
		return false;

	return !info->is_side_effecting ();
}
