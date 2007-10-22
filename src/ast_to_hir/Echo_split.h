/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert echo()es to print()s
 */

#ifndef PHC_ECHO_SPLIT_H
#define PHC_ECHO_SPLIT_H

#include "AST_transform.h"
#include "fresh.h"
#include "Shredder.h"

// Split echos into multiple statements. Normal function calls evaluate all
// their actual parameters at once, and then call the expression with the
// results of the evaluations. Echo, however, only evaluates its next argument
// after printing the result of the previouis argument. Functions with
// side-effects will display this.
//
// Convert
//	  echo f (), f();
//	into
//	  print f();
//	  print f();
//
//	We convert to print simply so the later print transformation is easier.
class Echo_split : public AST_transform
{
	void pre_eval_expr(AST_eval_expr* in, List<AST_statement*>* out)
	{
		AST_method_invocation* echo = new AST_method_invocation (
				NULL,	
				new Token_method_name (new String("echo")),
				NULL); // match any list (note this doesnt get populated. Use in STMT get the list.)

		if (not in->expr->match (echo))
		{
			out->push_back (in);
			return;
		};

		List<AST_actual_parameter*>* params =
			(dynamic_cast <AST_method_invocation*> (in->expr))->actual_parameters;
		assert (params);

		List<AST_actual_parameter*>::const_iterator i;
		for (i = params->begin (); i != params->end(); i++)
		{
			out->push_back (new AST_eval_expr (
							new AST_method_invocation (
								NULL,
								new Token_method_name (new String ("print")),
								new List<AST_actual_parameter*> (*i))));

		}
	}
};



#endif // PHC_ECHO_SPLIT_H
