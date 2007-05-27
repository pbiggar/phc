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
