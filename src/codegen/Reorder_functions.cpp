#include "Reorder_functions.h"

// Move functions to the front of the list.
void 
Reorder_functions::pre_php_script (AST_php_script *in)
{
	List<AST_statement*> *statements = new List<AST_statement*> ();
	List<AST_statement*> *functions = new List<AST_statement*> ();

	AST_method* pattern = new Wildcard<AST_method>;

	List<AST_statement*>::const_iterator i;
	for (i = in->statements->begin (); i != in->statements->end (); i++)
	{
		if ((*i)->match (pattern))
			functions->push_back (*i);
		else
			statements->push_back (*i);
	}
	functions->push_back_all (statements);
	in->statements = functions;
}
