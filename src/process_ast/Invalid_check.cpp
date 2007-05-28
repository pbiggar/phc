/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check for invalid PHP, which otherwise fits within the constraints of
 * our language. This should be run after the parser so we dont operate
 * on invalid code, and any time we worry we may generate invalid code in
 * the HIR.
 */
#include "Invalid_check.h"


void Invalid_check::pre_statement (AST_statement* in)
{
	// $x[]; or $x[][0]
	// These are represented as lists with NULL entries
	Wildcard<AST_variable> *wild = new Wildcard<AST_variable> ();

	if (in->match (new AST_eval_expr (wild)))
	{
		if (wild->value->array_indices)
		{
			List<AST_expr*>::const_iterator i;
			for (i = wild->value->array_indices->begin (); i != wild->value->array_indices->end (); i++)
			{
				if (*i == NULL)
					phc_error ("Cannot use [] for reading", in->get_filename (), in->get_line_number ());
			}
		}
	}
}

void Invalid_check::pre_assignment (AST_assignment* in)
{
	// $x =& array (); or $x =& 5;
	// These are syntax errors, but we're able to add them later (especially in foreach lowering)
	if (in->is_ref)
	{
		if (in->match (new AST_assignment (new Wildcard<AST_variable>, true, new Wildcard<AST_array>)))
		{
			phc_error ("Cannot assign a reference to a literal array", in->get_filename (), in->get_line_number ());
		}

		// FIXME: Cant use AST_literal in a wildcard. 
		if (in->match (new AST_assignment (new Wildcard<AST_variable>, true, new Wildcard<Token_real>))
				or in->match (new AST_assignment (new Wildcard<AST_variable>, true, new Wildcard<Token_int>))
				or in->match (new AST_assignment (new Wildcard<AST_variable>, true, new Wildcard<Token_string>))
				or in->match (new AST_assignment (new Wildcard<AST_variable>, true, new Wildcard<Token_bool>))
				or in->match (new AST_assignment (new Wildcard<AST_variable>, true, new Wildcard<Token_null>)))
		{
			phc_error ("Cannot assign a reference to a literal", in->get_filename (), in->get_line_number ());
		}
	}
}

void Invalid_check::pre_foreach (AST_foreach* in)
{
	// foreach (21 as $x) {}
	// PHP only gives this as a warning, but its using run-time values, and we
	// know this is a semantic error.
	
	// FIXME this is a good example of why we need is_literal. Note that the
	// tests above would also benefit. Its a lot of code to test something very
	// simple.
	if (dynamic_cast<AST_literal*> (in->expr))
	{
		phc_error ("Invalid (literal) expression supplied for foreach()",
			in->expr->get_filename (), in->expr->get_line_number ());
	}
}

void Invalid_check::pre_interface_def (AST_interface_def* in)
{
	// interface X { $var x; }
	// Interfaces arent allowed have non-const attributes
	List<AST_member*>::const_iterator i;
	for (i = in->members->begin (); i != in->members->end (); i++)
	{
		Wildcard<AST_attr_mod> *attr_mod = new Wildcard<AST_attr_mod>;

		if ((*i)->match (new AST_attribute (attr_mod, new Wildcard<Token_variable_name>, new Wildcard<AST_expr>)))
			if (!attr_mod->is_const)
				phc_warning ("Interfaces may not include member variables", 
						in->members->front()->get_filename(), in->members->front()->get_line_number ());
	}
}
