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
	// $x[];
	if (in->match (new AST_eval_expr (new AST_variable (
			new Wildcard<AST_target>, new Wildcard<AST_variable_name>, new List<AST_expr*> (NULL)))))
	{
		phc_error ("Cannot use [] for reading", in->get_filename (), in->get_line_number ());
	}
}
