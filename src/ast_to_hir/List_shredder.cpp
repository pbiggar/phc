/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Shred lists.
 */

#include "process_ir/fresh.h"

#include "List_shredder.h"

// TODO: needed for is_ref_literal. Refactor.
#include "process_ast/Invalid_check.h"

using namespace AST;

// Some shredding will create variables which may be missed if done
// at the same time as the variable shredding.

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

Expr* List_shredder::post_list_assignment(List_assignment* in)
{
	Variable* temp = fresh_var("PLA");

	assert (in->expr != NULL);

	bool use_ref = !is_ref_literal (in->expr);
	pieces->push_back(
			new Eval_expr(
				new Assignment(temp->clone (), use_ref, in->expr)));


	// reverse order
	List_element_list::reverse_iterator i;
	int counter = in->list_elements->size () - 1;
	for (i = in->list_elements->rbegin (); 
			i != in->list_elements->rend ();
			i++)
	{
		// create the RHS
		Expr_list *array_indices = new Expr_list ();
		array_indices->push_back (new INT (counter));
		Variable* rhs = new Variable (
				NULL,
				temp->variable_name->clone(),
				array_indices);
		counter --;

		// list ($x, , $z) leaves a NULL
		if (*i == NULL)
			continue;

		// create the LHS
		// its either a variable or a nested list element
		Nested_list_elements* nested 
			= dynamic_cast <Nested_list_elements*> (*i);
		if (nested)
		{
			// convert into a list_assignment, and repeat
			pieces->push_back (new Eval_expr (
						post_list_assignment (
							new List_assignment (nested->list_elements, rhs))));
		}
		else
		{
			Variable* var = dynamic_cast <Variable*> (*i);
			assert (var);
			// $c = $PLA[2];
			pieces->push_back( 
					new Eval_expr(
						new Assignment(var, false, rhs)));
		}
	}
	assert (counter == -1);

	// lists evaluate to their rvalue
	return temp;
}
