/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Shred lists.
 */

#ifndef PHC_EARLY_SHREDDER_H
#define PHC_EARLY_SHREDDER_H

#include "Lower_expr.h"
#include "fresh.h"

// Some shredding will create variables which may be missed if done
// at the same time as the variable shredding.
class List_shredder : public Lower_expr
{
public:

	/* Shred
	 *  $x = (list ($a, $b, $c) = array ($c, $b, a));
	 * into
	 *	  $PLA = array ($c, $b, $a);
	 *	  $c = $PLA[2];
	 *	  $b = $PLA[1];
	 *	  $a = $PLA[0];
	 *	  $x = $PLA; // note that left evaluates to the RHS of the assignment
	 *
	 *	Note the reverse order. This matters if you've arrays on the lhs.
	 *	Note that references arent allowed here.
	 */

	AST_expr* post_list_assignment(AST_list_assignment* in)
	{
		AST_variable* temp = fresh_var("PLA");

		assert (in->expr != NULL);

		bool use_ref = !is_ref_literal (in->expr);
		pieces->push_back(
				new AST_eval_expr(
					new AST_assignment(temp->clone (), use_ref, in->expr)));


		// reverse order
		List<AST_list_element*>::const_reverse_iterator i;
		int counter = in->list_elements->size () - 1;
		for (i = in->list_elements->rbegin (); 
				i != in->list_elements->rend ();
				i++)
		{
			// create the RHS
			List<AST_expr*> *array_indices = new List<AST_expr*> ();
			array_indices->push_back (new Token_int (counter));
			AST_variable* rhs = new AST_variable (
					NULL,
					temp->variable_name->clone(),
					array_indices);
			counter --;

			// list ($x, , $z) leaves a NULL
			if (*i == NULL)
				continue;

			// create the LHS
			// its either a variable or a nested list element
			AST_nested_list_elements* nested 
				= dynamic_cast <AST_nested_list_elements*> (*i);
			if (nested)
			{
				// convert into a list_assignment, and repeat
				pieces->push_back (new AST_eval_expr (
							post_list_assignment (
								new AST_list_assignment (nested->list_elements, rhs))));
			}
			else
			{
				AST_variable* var = dynamic_cast <AST_variable*> (*i);
				assert (var);
				// $c = $PLA[2];
				pieces->push_back( 
						new AST_eval_expr(
							new AST_assignment(var, false, rhs)));
			}
		}
		assert (counter == -1);

		// lists evaluate to their rvalue
		return temp;
	}
};


#endif // PHC_EARLY_SHREDDER_H
