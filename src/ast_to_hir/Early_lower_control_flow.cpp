/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower AST constructs into simpler constructs which are still PHP.
 */

#include "Early_lower_control_flow.h"
#include "process_ir/General.h"
#include <sstream>

using namespace AST;

/* Convert
 *		foreach ($x as $y[$z] => $w[4]) { ... }
 *	into
 *		foreach ($x as $T => $T2)
 *		{
 *			$y[$z] = $T; // & is not allowed in PHP
 *			$w[4] = $T2; // & is allowed here
 *		}
 */
void Early_lower_control_flow::post_foreach (Foreach* in, Statement_list* out)
{
	// We use push_front, so do value first
	if (not in->val->is_simple_variable ())
	{
		Variable* temp = fresh_var ("Elcfv");
		in->statements->push_front (
			new Eval_expr (
				new Assignment (
					in->val,
					in->is_ref,
					temp)));
		in->val = temp->clone ();
	}
	
	if (in->key && not in->key->is_simple_variable ())
	{
		Variable* temp = fresh_var ("Elfck");
		in->statements->push_front (
			new Eval_expr (
				new Assignment (
					in->key,
					false,
					temp)));
		in->key = temp->clone ();
	}

	out->push_back (in);
}

/* Convert
 *			while ($x) { y (); }
 * into
 *			while (true)
 *			{
 *				if ($x) ;
 *				else break;
 *
 *				y ();
 *			}
 */

void Early_lower_control_flow::post_while (While* in, Statement_list* out)
{
	(*out
		<< "while (true)"
		<< "{"
		<< "	if (!(" << in ->expr << ")) break;"
		<< "}").finish (in);
	
	While* w = dynamic_cast<While*> (out->back ());
	w->statements->push_back_all (in->statements);
}

/* Convert
 *		do { y (); continue; } 
 *		while ($x)
 * into
 *		$first = true;
 *		while (true)
 *		{
 *			if ($first) $first = false;
 *			else if (!$x) break;
 *			y ();
 *			continue;
 *		}
 *
 *	This is a little odd, but it accounts for the continue statement, which is
 *	difficult to handle otherwise.
 */
void Early_lower_control_flow::post_do (Do* in, Statement_list* out)
{
	Variable* first = fresh_var ("ElcfPD");
	(*out
		<< first << " = true;"
		<< "while (true)"
		<< "{"
		<< "	if (" << first << ") " << first << " = false;"
		<< "	else if (!(" << in ->expr << ")) break;"
		<< "}").finish (in);
	
	While* w = dyc<While> (out->back ());
	w->statements->push_back_all (in->statements);
}

/* Convert
 *			for (i = 0; i < N; i++) { y (); continue; }
 * into
 *			i = 0;
 *			$first = true;
 *			while (true)
 *			{
 *				if ($first) $first = false;
 *				else $i++; // only performed after first iteration
 *
 *				if (i < N) ;
 *				else break;
 *
 *				y ();
 *			}
 */

void Early_lower_control_flow::post_for (For* in, Statement_list* out)
{
	/* Note that any of in->expr, in->init and in->incr can be NULL (eg in "for
	 * (;;)". Also, each expr can be a comma-op. Between these two, its best not
	 * to use a parse_buffer. */

	//	i = 0;
	if (in->init)
		out->push_back (new Eval_expr (in->init));


	// $first = true;
	Variable* first = fresh_var ("ElcfPF");
	out->push_back (
		new Eval_expr (
			new Assignment (
				first,
				false,
				new BOOL (true))));


	// while (true)
	While *w = new While (new BOOL (true), new Statement_list);

	//		if ($first) $first = false;
	//		else $i++; // only performed after first iteration
	Statement_list* false_stmts = new Statement_list;
	if (in->incr) false_stmts->push_back (new Eval_expr (in->incr));
	w->statements->push_back (
			new If (
				first->clone (),
				new Statement_list (
					new Eval_expr (
						new Assignment (
							first->clone (),
							false,
							new BOOL (false)))),
				false_stmts));


	//		if (i < N) ;
	//		else break;	
	if (in->cond == NULL) 
		in->cond = new BOOL (true);
	w->statements->push_back (
			new If (
				in->cond,
				new Statement_list,
				new Statement_list (
					new Break (NULL))));

	//		y ();
	w->statements->push_back_all (in->statements);

	w->clone_mixin_from (in); // get line numbers
	out->push_back (w);

}

/* A switch statement is not an easy thing to replace, due to myriads of corner
 * cases, mostly involving fall-through.
 *
 * Break and continue are supported by wrapping the statements in a do {..}
 * while (0) loop. break $x is also supported by this.
 *
 * There can be multiple default statements. In this case, only the last one
 * can be matched. But other case statements can fall-through into a default
 * which doesnt match.
 *
 * Fall-through edges are tricky. Because there may be a break, and its
 * non-trivial (in the general case) to find out if theres a break, so we
 * always let code fall-through. If there is a break, it will catch. If not,
 * check that we have matched already.
 *
 * All blocks are added in order, so they may fall-through. However, we should
 * not evaluate the condition for a fall-through, as it may have side-effects.
 *
 * The last default block gets all subsequent code blocks added to it. This
 * leads to some code duplication, but we'll let the optimizer deal with it.
 * 
 * Convert
 *		switch (expr)
 *		{
 *			case expr1:
 *				x1 ();
 *
 *			default:
 *				xD1;
 *				break;
 *
 *			case expr2:
 *				x2 ();
 *				break;
 *			...
 *			default: // only the last default counts
 *				xD2 ();
 *
 *			case expr3:
 *				x3 ();
 *		}
 *
 *	into
 *		val = expr;
 *		matched = false;
 *		do
 *		{
 *			// case expr1
 *			if (!matched)
 *			{
 *				val1 = expr1;
 *				if (val == val1)
 *					matched = true;
 *			}
 *			if (matched)
 *				x1 ();
 *
 *
 *			// default - put the code for the default, in case of fall-through
 *			// (even though a later default overrides a possible match)
 *			if (matched)
 *				xD1 ();
 *
 *
 *			// case expr2
 *			if (!matched)
 *			{
 *				val2 = expr2;
 *				if (val == expr2)
 *					matched = true;
 *			}
 *			if (matched)
 *			{
 *				x2 ();
 *				break; // this will break the outer loop
 *			}
 *
 *
 *			// case expr3
 *			if (!matched)
 *			{
 *				val3 = expr3;
 *				if (val == val3)
 *					matched = true;
 *			}
 *
 *			// default
 * 		if (matched)
 *				xD1 ();
 *
 *			if (matched)
 *			{
 *				x3 ();
 *			}
 *
 *			// default with actual matching
 *			if (!matched)
 *			{
 *				matched = true;
 *			}
 *			xD ();
 *
 *			if (!matched)
 *			{
 *				xD2 ();
 *				x3 ();
 *			}
 *		} while (0)
 *
 *	Use a pre_switch so that the do_while can be lowered in the post_do.
 */
void Early_lower_control_flow::pre_switch(Switch* in, Statement_list* out)
{
	// val = expr;
	Variable *switch_val = fresh_var ("TEL");
	out->push_back (new Eval_expr (
		new Assignment (
			switch_val, 
			false, 
			in->expr)));

	// matched = false
	Variable *matched_val = fresh_var ("TSM");
	out->push_back (new Eval_expr (
		new Assignment (
			matched_val, 
			false, 
			new BOOL (false))));

	// do {
	Do* wrapper = new Do (new Statement_list, new BOOL (false));

	// The default expression gets its statements and all statements
	// after it.
	Statement_list* default_statements = NULL;

	foreach (Switch_case* sc, *in->switch_cases)
	{
		// Only evaluate a case expression if it hasnt been matched
		// already.
		if (sc->expr != NULL) // case $var:
		{
			Statement_list* body = new Statement_list;

			// if (!matched)
			wrapper->statements->push_back (
				new If (
					matched_val->clone (),
					new Statement_list,
					body));

			// TODO if its a var, we dont need to extract it
			//	val1 = expr1;
			Variable *expr_var = fresh_var ("TL");
			body->push_back (new Eval_expr (
				new Assignment (
					expr_var, 
					false, 
					sc->expr)));

			// if (val == val1) matched = true;
			body->push_back (new If (
				new Bin_op (
					switch_val->clone (), 
					new OP (new String ("==")), 
					expr_var->clone ()),
				new Statement_list (
					new Eval_expr (
						new Assignment (
							matched_val->clone (), 
							false, 
							new BOOL (true)))),
				new Statement_list));
		}
		else
		{
			// reset the list of default statements
			default_statements = new Statement_list;
		}


		// if (matched) { statements; ... ; }
		wrapper->statements->push_back (
			new If (
				matched_val->clone (),
				sc->statements,
				new Statement_list));

		

		// The default case gets a copy of all statements which occur
		// after it.
		if (default_statements)
			default_statements->push_back_all (sc->statements->clone ());
	}


	// Add the last default case added
	if (default_statements)
	{
		// if (!matched) { statements; ... ; }
		wrapper->statements->push_back (
			new If (
				matched_val->clone (),
				new Statement_list,
				default_statements)); // negate
	}

	out->push_back (wrapper);
}
