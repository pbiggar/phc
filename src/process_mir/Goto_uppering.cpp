/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert goto statements, branches and labels into a FSM, which will consist
 * of a while loop, a switch statement, a state variable, and a lot of
 * continues.
 */

#include "Goto_uppering.h"

using namespace AST;

Goto_uppering::Goto_uppering ()
{
	next = new Variable (NULL, new VARIABLE_NAME (new String ("__next")), new List<Expr*>);
	start = new STRING (new String ("start"));
	end = new STRING (new String ("end"));
}

/* We dont want to run this on all statement bodies in the traversal order.  So
 * we call it manually at the right times. */
List<Statement*>*
Goto_uppering::convert_statement_list (List<Statement*> *in)
{
	// The prelude contains all static declarations
	List<Statement*> *prelude = new List<Statement*> ();

	// OUT only contains the while, and the "start" statement.
	List<Statement*> *out = new List<Statement*> ();

	// add $next = "start";
	Assignment *init = new Assignment (next->clone (), false,
			start->clone ());
	out->push_back (new Eval_expr (init));

	// create 'switch ($next)' (cases is to be used later)
	List<Switch_case*> *cases = new List<Switch_case*> ();
	Switch *switches = new Switch (next->clone (), cases);

	// Add: while (true) { switch ($next) { } }
	BOOL *truth = new BOOL (true);
	While *while_stmt = new While (truth, new List<Statement*> ());
	out->push_back (while_stmt);
	while_stmt->statements->push_back (switches);


	// Add: case "start";
	Switch_case* current = new Switch_case (start->clone (), new List<Statement*> ());
	cases->push_back (current);


	// set up patterns
	Wildcard<Expr> *expr = new Wildcard<Expr> ();
	Wildcard<LABEL_NAME> *l1 = new Wildcard<LABEL_NAME> ();
	Wildcard<LABEL_NAME> *l2 = new Wildcard<LABEL_NAME> ();
	Goto *goto_pattern = new Goto (l1);
	Branch *branch_pattern = new Branch (expr, l1, l2);
	Label *label_pattern = new Label (l1);;

	// Convert all the patterns
	List<Statement*>::const_iterator i;
	for (i = in->begin (); i != in->end (); i++)
	{
		// add statements to the current case statement
		if ((*i)->match (goto_pattern))
		{
			// add the gotos to the current case statement
			current->statements->push_back (
					new Eval_expr (
						new Assignment (next->clone (), false,
							new STRING (l1->value->value))));

			current->statements->push_back (new Continue (NULL));
		}
		else if ((*i)->match (branch_pattern))
		{
			// add the if and gotos to the current case statement
			If *iffy = new If (expr->value, 
					new List<Statement*>(), 
					new List<Statement*>());

			iffy->iftrue->push_back (
					new Eval_expr (
						new Assignment (next->clone (), false,
							new STRING (l1->value->value) )));
			iffy->iftrue->push_back (new Continue (NULL));

			iffy->iffalse->push_back (
					new Eval_expr (
						new Assignment (next->clone (), false,
							new STRING (l2->value->value) )));
			iffy->iffalse->push_back (new Continue (NULL));

			current->statements->push_back (iffy);
		}
		else if ((*i)->match (label_pattern))
		{
			// finish the current case statement and start a new one
			current = new Switch_case (
					new STRING (l1->value->value), 
					new List<Statement*> ());
			cases->push_back (current);
		}
		else
		{
			if (((*i)->attrs->is_true ("phc.lower_control_flow.top_level_declaration")))
				prelude->push_back(*i);
			else
				current->statements->push_back(*i);
		}
	}

	// add '$next = "end";' after the final statement
	current->statements->push_back (new Eval_expr (
				new Assignment (next->clone (), false,
					end->clone ())));


	// add the breaking statement
	current = new Switch_case (
			end->clone (),
			new List<Statement*> ());
	cases->push_back (current);
	current->statements->push_back (new Break (new INT (2)));


	// combine the two lists, and output all statements
	prelude->push_back_all (out);
	return prelude;
}

void 
Goto_uppering::pre_php_script (PHP_script *in)
{
	in->statements = convert_statement_list (in->statements);
}

void 
Goto_uppering::pre_method (Method *in)
{
	if(in->statements != NULL) // abstract method?
		in->statements = convert_statement_list (in->statements);
}

void Goto_uppering::post_php_script (PHP_script* in)
{
//	in->visit (new Check_uppering ());
}
