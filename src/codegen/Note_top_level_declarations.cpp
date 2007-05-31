/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower any control flow statements into conditional
 * gotos, and add necessary labels.
 */

#include "Note_top_level_declarations.h"

/* PHP treats top level class and function declarations as if they are declared
 * immediately upon loading the script. Dynamic declarations, however, are only
 * loaded when the statement is executed. We mark top-level statements now,
 * since we'll lose that information later */
void Note_top_level_declarations::pre_php_script (AST_php_script* in)
{
	List<AST_statement*>::const_iterator i;
	for (i = in->statements->begin (); i != in->statements->end (); i++)
	{
		if ((*i)->classid () == AST_method::ID
			|| (*i)->classid () == AST_class_def::ID
			|| (*i)->classid () == AST_interface_def::ID)
		{
			(*i)->attrs->set_true ("phc.lower_control_flow.top_level_declaration");
		}
	}
}


