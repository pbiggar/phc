/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lift functions and classes to the global scope, and introduce "__MAIN__" 
 *
 */

#include "Lift_functions_and_classes.h"

using namespace AST;

void Lift_functions_and_classes::children_php_script(PHP_script* in)
{
	List<Statement*>* main = new List<Statement*>;
	List<Statement*>* top_level_statements = new List<Statement*>;

	// move all non-declaration statements into main
	List<Statement*>::const_iterator i;
	for (i = in->statements->begin (); i != in->statements->end (); i++)
	{
		if (((*i)->attrs->is_true ("phc.lower_control_flow.top_level_declaration")))
			top_level_statements->push_back(*i);
		else
			main->push_back(*i);

	}

	top_level_statements->push_back(new Method(
		new Signature(
			new Method_mod(),
			false,
			new METHOD_NAME(new String("__MAIN__")),
			new List<Formal_parameter*>),
		main));

	in->statements = top_level_statements;
}
