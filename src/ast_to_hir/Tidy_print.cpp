/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert print()s into to printf()s
 */

#include "Tidy_print.h"
#include "process_ir/General.h"
#include "process_ir/fresh.h"

using namespace AST;

void Tidy_print::pre_eval_expr (Eval_expr* in, List<Statement*>* out)
{
	Assignment* agn = dynamic_cast<Assignment*> (in->expr);

	/* Convert print, in a similar fashion to echo. Print can only have 1 parameter though, and always return 1.
	 *   $x = print $y;
	 * into
	 *   printf ("%s", $y); // $t2 can be discarded
	 *   $x = 1;
	 *
	 * If $x is unused, we have
	 *	  printf ("%s", $y);
	 */
	Wildcard<Expr>* arg = new Wildcard<Expr>;
	Method_invocation* print = new Method_invocation (
			NULL,	
			new METHOD_NAME (new String ("print")),
			new List<Actual_parameter*> (
				new Actual_parameter (false, arg) // print can only have 1 argument
				));

	Expr* expr = in->expr;

	if (agn)
		expr = agn->expr;
	
	if (expr->match (print))
	{
		// printf ("%s", expr);
		(*out
			<< "printf (\"%s\", " << arg->value << ");"
		).to_pass (s("tidyp"), expr);
		
		// This isnt necessary 
		if (agn)
		{
			// $x = 1;
			out->push_back (new Eval_expr (
						new Assignment(agn->variable, false,
							new INT (1))));
		}
		return;
	}
	else
	{
		out->push_back (in);;
	}
}
