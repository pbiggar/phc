/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower any control flow statements into conditional
 * gotos, and add necessary labels.
 */

#include "Note_top_level_declarations.h"

using namespace AST;

/* PHP treats top level class and function declarations as if they are declared
 * immediately upon loading the script. Dynamic declarations, however, are only
 * loaded when the statement is executed. We mark top-level statements now,
 * since we'll lose that information later */
void Note_top_level_declarations::pre_php_script (PHP_script* in)
{
	List<Statement*>::const_iterator i;
	for (i = in->statements->begin (); i != in->statements->end (); i++)
	{
		if ((*i)->classid () == Method::ID
			|| (*i)->classid () == Class_def::ID
			|| (*i)->classid () == Interface_def::ID)
		{
			(*i)->attrs->set_true ("phc.lower_control_flow.top_level_declaration");
		}
	}
}


