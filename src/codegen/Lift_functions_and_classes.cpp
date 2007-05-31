/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lift functions and classes to the global scope, and introduce "__MAIN__" 
 *
 */

#include "Lift_functions_and_classes.h"

void Lift_functions_and_classes::children_php_script(AST_php_script* in)
{
	List<AST_statement*>* main = new List<AST_statement*>;
	List<AST_statement*>* top_level_statements = new List<AST_statement*>;

	// move all non-declaration statements into main
	List<AST_statement*>::const_iterator i;
	for (i = in->statements->begin (); i != in->statements->end (); i++)
	{
		if (((*i)->attrs->is_true ("phc.lower_control_flow.top_level_declaration")))
			top_level_statements->push_back(*i);
		else
			main->push_back(*i);

	}

	top_level_statements->push_back(new AST_method(
		new AST_signature(
			new AST_method_mod(),
			false,
			new Token_method_name(new String("__MAIN__")),
			new List<AST_formal_parameter*>),
		main));

	in->statements = top_level_statements;
}
