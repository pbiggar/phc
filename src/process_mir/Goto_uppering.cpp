/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert goto statements, branches and labels into a FSM, which will consist
 * of a while loop, a switch statement, a state variable, and a lot of
 * continues.
 */

#include "Goto_uppering.h"
#include "MIR_to_AST.h"
#include "process_ir/General.h"

using namespace MIR;

Goto_uppering::Goto_uppering ()
{
	ast_next = new AST::Variable (new AST::VARIABLE_NAME (s("__next")));
	next = new MIR::VARIABLE_NAME (s("__next"));
}

/* We dont want to run this on all statement bodies in the traversal order.  So
 * we call it manually at the right times. */
Statement_list*
Goto_uppering::convert_statement_list (Statement_list *in)
{
	// The prelude contains all class and function declarations
	Statement_list *prelude = new Statement_list;

	// OUT only contains the while, and the "start" statement.
	Statement_list *out = new Statement_list;


	// $next = "start";
	(*out
		<< "$__next = \"start\";"
	).finish (next);

	// switch ($next)
	AST::Switch_case_list *cases = new AST::Switch_case_list;
	AST::Switch *switches = 
		new AST::Switch (
			ast_next->clone (),
			cases);


	// while (true) { switch ($next) { } }
	out->push_back (new FOREIGN (
		new AST::While (
			new AST::BOOL (true),
			new AST::Statement_list (
				switches))));


	// case "start";
	AST::Switch_case* current = 
		new AST::Switch_case (
			new AST::STRING (s("start")),
			new AST::Statement_list);

	cases->push_back (current);


	// set up patterns
	Wildcard<VARIABLE_NAME> *var_name = new Wildcard<VARIABLE_NAME> ();
	Wildcard<LABEL_NAME> *l1 = new Wildcard<LABEL_NAME> ();
	Wildcard<LABEL_NAME> *l2 = new Wildcard<LABEL_NAME> ();
	Goto *goto_pattern = new Goto (l1);
	Branch *branch_pattern = new Branch (var_name, l1, l2);
	Label *label_pattern = new Label (l1);;

	// Convert all the patterns
	foreach (Statement* s, *in)
	{
		// add statements to the current case statement
		if (s->match (goto_pattern))
		{
			// add the gotos to the current case statement
			(*current->statements 
				<<	ast_next << " = \"" << l1->value->value << "\";"
				<< "continue;"
			).finish (ast_next); // we dont care about attributes
		}
		else if (s->match (branch_pattern))
		{
			// add the if and gotos to the current case statement
			(*current->statements 
				<< "if ($" << *var_name->value->value << ")"
				<< "{"
				<<		ast_next << " = \"" << l1->value->value << "\";"
				<<	"	continue;"
				<< "}"
				<< "else"
				<< "{"
				<<		ast_next << " = \"" << l2->value->value << "\";"
				<<	"	continue;"
				<< "}"
			).finish (ast_next); // we dont care about attributes
		}
		else if (s->match (label_pattern))
		{
			// case "l1":
			current = new AST::Switch_case (
				new AST::STRING (l1->value->value), 
				new AST::Statement_list);

			cases->push_back (current);
		}
		else
		{
			if ((s->attrs->is_true ("phc.lower_control_flow.top_level_declaration")))
				prelude->push_back(s);
			else
				current->statements->push_back((new MIR_to_AST ())->fold_statement (s));
		}
	}

	// add '$next = "end";' after the final statement
	(*current->statements
		<<	ast_next << " = \"end\";"
	).finish (ast_next);

	// add the breaking statement
	current = new AST::Switch_case (
			new AST::STRING (s("end")),
			new AST::Statement_list);
	cases->push_back (current);

	(*current->statements
		<< "break 2;"
	).finish (ast_next);


	// combine the two lists, and output all statements
	prelude->push_back_all (out);
	return prelude;
}

void 
Goto_uppering::pre_php_script (PHP_script *in)
{
	bool add_call_to_main = false;
	if (in->statements->size() > 0 && isa<Method> (in->statements->front()))
	{
		Method* m = dyc<Method> (in->statements->front());
		if (*m->signature->method_name->value == "__MAIN__")
			add_call_to_main = true;
	}

	in->statements = convert_statement_list (in->statements);

	if (add_call_to_main)
		(*in->statements
			<< "__MAIN__();"
		).finish (in);
}

void 
Goto_uppering::pre_method (Method *in)
{
	if(in->statements != NULL) // abstract method
		in->statements = convert_statement_list (in->statements);
}
