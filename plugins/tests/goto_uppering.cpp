/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert goto statements, branches and labels into a FSM, which will consist
 * of a while loop, a switch statement, a state variable, and a lot of
 * continues.
 *
 * For example:
 * if ($x == 7) goto L0 else goto L1;
 *	L0:
 *		$y = 12;
 *		goto L2;
 *	L1:
 *		$y = 18;
 *		goto L2;
 *	L2:
 *	
 *	is converted to:
 *	
 *	$next = "start";
 *	while (true)   
 *	{  
 *		switch ($next)      
 *		{           
 *			case "start":
 *				if ($x == 7) { $next = "L0"; continue; }
 *				else { $next = "L1"; continue; }
 *			case "L0": 
 *				$y = 12;                    
 *				$next = "L2";
 *				continue;
 *			case "L1":
 *				$y = 18;
 *				$next = "L2";
 *				continue;
 *			case "L2":
 *				$next = "end"; 
 *				continue;
 *			case "end":
 *				break 2;
 *			default:
 *				assert (0 && "fail");
 *		}
 *	}	
 *
 *
 *	This be trivially done by adding code at the start and end, and replacing
 *	gotos and labels with their respective constructs.
 */

#include "AST_visitor.h"
class Goto_uppering : virtual public AST_visitor
{
private:
	AST_variable *next;
	Token_string *start;
	Token_string *end;
	AST_switch *switching;

public:
	Goto_uppering ()
	{
		next = new AST_variable (NULL, new Token_variable_name (new String ("__next")), new List<AST_expr*>);
		start = new Token_string (new String ("start"), new String ("start"));
		end = new Token_string (new String ("end"), new String ("end"));
	}

public:

	/* We dont want to run this on all statement bodies in the traversal order.
	 * So we call it manually at the right times. */
	List<AST_statement*>* convert_statement_list (List<AST_statement*> *in)
	{
		// this in only contains the while, and the "start" statement.
		List<AST_statement*> *out = new List<AST_statement*> ();

		// add $next = "start";
		AST_assignment *init = new AST_assignment (next->clone (), false,
				start->clone ());
		out->push_back (new AST_eval_expr (init));

		// create 'switch ($next)' (cases is to be used later)
		List<AST_switch_case*> *cases = new List<AST_switch_case*> ();
		AST_switch *switches = new AST_switch (next->clone (), cases);

		// create 'while (true)' and add the switch to it
		Token_bool *truth = new Token_bool (true, new String ("true"));
		AST_while *while_stmt = new AST_while (truth, new List<AST_statement*> ());
		out->push_back (while_stmt);
		while_stmt->statements->push_back (switches);


		// case "start";
		AST_switch_case* current = new AST_switch_case (start->clone (), new List<AST_statement*> ());
		cases->push_back (current);


		// set up patterns
		Wildcard<AST_expr> *expr = new Wildcard<AST_expr> ();
		Wildcard<Token_label_name> *l1 = new Wildcard<Token_label_name> ();
		Wildcard<Token_label_name> *l2 = new Wildcard<Token_label_name> ();
		AST_goto *goto_pattern = new AST_goto (l1);
		AST_branch *branch_pattern = new AST_branch (expr, l1, l2);
		AST_label *label_pattern = new AST_label (l1);;

		List<AST_statement*>::const_iterator i;
		for (i = in->begin (); i != in->end (); i++)
		{
			// add statements to the current case statement
			if ((*i)->match (goto_pattern))
			{
				// add the gotos to the current case statement
				current->statements->push_back (
						new AST_eval_expr (
							new AST_assignment (next->clone (), false,
								new Token_string (l1->value->value, l1->value->value))));

				current->statements->push_back (new AST_continue (NULL));
			}
			else if ((*i)->match (branch_pattern))
			{
				// add the if and gotos to the current case statement
				AST_if *iffy = new AST_if (expr->value, 
						new List<AST_statement*>(), 
						new List<AST_statement*>());

				iffy->iftrue->push_back (
						new AST_eval_expr (
							new AST_assignment (next->clone (), false,
								new Token_string (l1->value->value, l1->value->value) )));
				iffy->iftrue->push_back (new AST_continue (NULL));

				iffy->iffalse->push_back (
						new AST_eval_expr (
							new AST_assignment (next->clone (), false,
								new Token_string (l2->value->value, l2->value->value) )));
				iffy->iffalse->push_back (new AST_continue (NULL));

				current->statements->push_back (iffy);
			}
			else if ((*i)->match (label_pattern))
			{
				// finish the current case statement and start a new one
				current = new AST_switch_case (
						new Token_string (l1->value->value, l1->value->value), 
						new List<AST_statement*> ());
				cases->push_back (current);
			}
			else
			{
				current->statements->push_back (*i);
			}
		}

		// add '$next = "end";' after the final statement
		current->statements->push_back (new AST_eval_expr (
					new AST_assignment (next->clone (), false,
						new Token_string (new String ("end"), new String ("end")))));


		// add the breaking statement
		current = new AST_switch_case (
				new Token_string (new String ("end"), new String ("end")), 
				new List<AST_statement*> ());
		cases->push_back (current);
		current->statements->push_back (new AST_break (new Token_int (2, new String ("2"))));

		return out;
	}

	void pre_php_script (AST_php_script *in)
	{
		in->statements = convert_statement_list (in->statements);
	}

	void pre_method (AST_method *in)
	{
		in->statements = convert_statement_list (in->statements);
	}

};

extern "C" void process_ast(AST_php_script* script)
{
	Goto_uppering gup;
	script->visit (&gup);
}
