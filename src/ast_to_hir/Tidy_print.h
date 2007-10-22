/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert print()s into to printf()s
 */

#ifndef PHC_TIDY_PRINT_H
#define PHC_TIDY_PRINT_H

#include "AST_transform.h"
#include "fresh.h"
#include "Shredder.h"


class Tidy_print : public AST_transform
{
	void pre_eval_expr (AST_eval_expr* in, List<AST_statement*>* out)
	{
		AST_assignment* agn = dynamic_cast<AST_assignment*> (in->expr);

		/* Convert print, in a similar fashion to echo. Print can only have 1 parameter though, and always return 1.
		 *   $x = print $y;
		 * into
		 *   $t2 = printf ("%s", $y); // $t2 can be discarded
		 *   $x = 1;
		 *
		 * If $x is unused, we have
		 *	  $x = printf ("%s", $y);
		 */
		Wildcard<AST_expr>* arg = new Wildcard<AST_expr>;
		AST_method_invocation* print = new AST_method_invocation (
				NULL,	
				new Token_method_name (new String ("print")),
				new List<AST_actual_parameter*> (
					new AST_actual_parameter (false, arg) // print can only have 1 argument
					));

		if (agn && agn->expr->match (print))
		{
			// $t2 = printf ("%s", expr);
			bool unused = agn->variable->attrs->is_true ("phc.codegen.unused");

			AST_variable* t2 = agn->variable;
			if (not unused)
				t2 = fresh_var ("TSp");

			out->push_back_all (shred (
						new AST_eval_expr (
							new AST_assignment(t2, false,
								new AST_method_invocation(
									NULL,
									new Token_method_name(new String("printf")),
									new List<AST_actual_parameter*>(
										new AST_actual_parameter(
											false, 
											new Token_string(new String("%s"))),
										new AST_actual_parameter(
											false,
											arg->value)
										))))));


			// This isnt necessary 
			if (not unused)
			{
				// $x = 1;
				out->push_back (new AST_eval_expr (
							new AST_assignment(agn->variable, false,
								new Token_int (1))));
			}

			return;
		}
		else
		{
			out->push_back (in);;
		}
	}
};

#endif // PHC_TIDY_PRINT_H
