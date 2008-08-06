/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lift functions and classes to the global scope, and introduce "__MAIN__" 
 *
 */

#include "Lift_functions_and_classes.h"
#include "process_ir/General.h"

using namespace MIR;

void Lift_functions_and_classes::children_php_script(PHP_script* in)
{
	List<Statement*>* main = new List<Statement*>;
	List<Statement*>* top_level_statements = new List<Statement*>;

	// move all non-declaration statements into main
	foreach (Statement* s, *in->statements)
	{
		if ((s->attrs->is_true("phc.lower_control_flow.top_level_declaration")))
			top_level_statements->push_back(s);
		else
			main->push_back(s);

	}

	top_level_statements->push_back(new Method(
		new Signature(
			new Method_mod(),
			false,
			new METHOD_NAME(new String("__MAIN__")),
			new List<Formal_parameter*>),
		main));

	top_level_statements->back()->attrs->set_true("phc.lower_control_flow.top_level_declaration");

	in->statements = top_level_statements;
}
