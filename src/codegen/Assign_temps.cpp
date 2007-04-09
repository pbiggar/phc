/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Assign temporaries 
 *
 * TODO: Does not deal with nested function definitions.
 */

#include "Assign_temps.h"

void Assign_temps::pre_php_script(AST_php_script* in)
{
	next_global_fresh = 0;
	current_scope = GLOBAL_SCOPE;
}

void Assign_temps::post_php_script(AST_php_script* in)
{
	in->attrs->set("phc.codegen.num_temps", new Integer(next_global_fresh));
}

void Assign_temps::pre_method(AST_method* in)
{
	next_local_fresh = 0;
	current_scope = LOCAL_SCOPE;
}

void Assign_temps::post_method(AST_method* in)
{
	in->attrs->set("phc.codegen.num_temps", new Integer(next_local_fresh));
	current_scope = GLOBAL_SCOPE;
}

void Assign_temps::pre_expr(AST_expr* in)
{
	in->attrs->set("phc.codegen.temp", fresh());
}

Integer* Assign_temps::fresh()
{
	switch(current_scope)
	{
		case GLOBAL_SCOPE:
			return new Integer(next_global_fresh++);
		case LOCAL_SCOPE:
			return new Integer(next_local_fresh++);
	}
	
	assert(0);
}

