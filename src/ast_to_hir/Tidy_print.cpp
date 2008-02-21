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
	 *   $t2 = printf ("%s", $y); // $t2 can be discarded
	 *   $x = 1;
	 *
	 * If $x is unused, we have
	 *	  $x = printf ("%s", $y);
	 */
	Wildcard<Expr>* arg = new Wildcard<Expr>;
	Method_invocation* print = new Method_invocation (
			NULL,	
			new METHOD_NAME (new String ("print")),
			new List<Actual_parameter*> (
				new Actual_parameter (false, arg) // print can only have 1 argument
				));

	if (agn && agn->expr->match (print))
	{
		// $t2 = printf ("%s", expr);
		bool unused = agn->variable->attrs->is_true ("phc.codegen.unused");

		Variable* t2 = agn->variable;
		if (not unused)
			t2 = fresh_var ("TSp");

		out->push_back_all (lower_ast ("tidyp",
					new Eval_expr (
						new Assignment(t2, false,
							new Method_invocation(
								NULL,
								new METHOD_NAME(new String("printf")),
								new List<Actual_parameter*>(
									new Actual_parameter(
										false, 
										new STRING(new String("%s"))),
									new Actual_parameter(
										false,
										arg->value)
									))))));


		// This isnt necessary 
		if (not unused)
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
