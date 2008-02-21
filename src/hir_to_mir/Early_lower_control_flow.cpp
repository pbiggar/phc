/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower AST constructs into simpler constructs which are still PHP.
 */

#include "Early_lower_control_flow.h"
#include "Check_lowering.h"
#include "process_ir/fresh.h"
#include "process_ir/General.h"
#include <sstream>

using namespace AST;

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

void Early_lower_control_flow::post_while (While* in, List<Statement*>* out)
{
	Expr* expr = in->expr;

	in->expr = new BOOL (true); //	while (true)

	Break* b;

	in->statements->push_front (
		new If (expr,													// if ($x)
			new List<Statement*>,									//		;
			new List<Statement*> (b = new Break (NULL))));	// else break;

	
	b->clone_mixin_from (in); // get line numbers

	out->push_back (in);
}

/* Convert
 *		do { y (); } 
 *		while ($x)
 * into
 *		while (true)
 *		{
 *			y ();
 *			if ($x) ;
 *			else break;
 *		}
 */
void Early_lower_control_flow::post_do (Do* in, List<Statement*>* out)
{
	While* w = new While (new BOOL (true), in->statements); // while (true)

	Break* b;

	w->statements->push_back (
		new If (in->expr,												// if ($x)
			new List<Statement*>,									//		;
			new List<Statement*> (b = new Break (NULL))));	// else break;

	b->clone_mixin_from (in); // get line numbers
	out->push_back (w);
}

/* Convert
 *			for (i = 0; i < N; i++) y ();
 * into
 *			i = 0;
 *			while (true)
 *			{
 *				if (i < N) ;
 *				else break;
 *
 *				y ();
 *
 *				i++;
 *			}
*
 * This is done by converting into
 *			i = 0
 *			while (i < N)
 *			{
 *				y ();
 *				i++;
 *			}
 *	which is then lowered by post_while. */

void Early_lower_control_flow::post_for (For* in, List<Statement*>* out)
{
	/* Note that any of in->expr, in->init and in->incr can be NULL (eg in "for
	 * (;;)", so we have to handle all those cases. */

	if (in->cond == NULL) 
		in->cond = new BOOL (true);

	// create the while
	While *while_stmt = new While (in->cond, in->statements);
	while_stmt->clone_mixin_from (in); // get line numbers

	if (in->incr)
		while_stmt->statements->push_back (new Eval_expr (in->incr));

	// push it all back
	if (in->init)
		out->push_back (new Eval_expr (in->init));
	post_while (while_stmt, out);
}

/* A swithc statement can be simply replaced by nested-if
 * statements, which is the PHP semantics anyway. Break and continue
 * are supported by wrapping the statements in a do {..} while (0)
 * loop.
 *
 * Fall-through edges are tricky. Because there may be a break, and
 * its non-trivial (in the general case) to find out if theres a
 * break, we always let code fall-through. If there is a break, it
 * will catch. If not, the next if statement will check the current
 * condition aswell as the next condition.
 * 
 * Convert
 *		switch (expr)
 *		{
 *			case expr1:
 *				x1 ();
 *			case expr2:
 *				x2 ();
 *				break;
 *			...
 *			default exprD:
 *				xD ();
 *
 *			case expr3:
 *				x3 ();
 *		}
 *
 *	into
 *		val = expr;
 *		do
 *		{
 *			val1 = expr1;
 *			if (val == val1)
 *			{
 *				x1 ();
 *			}
 *
 *			val2 = expr2;
 *			if (val == expr2 || val == expr1) // check both conditions
 *			{
 *				x2 ();
 *				break; // this will break the loop
 *			}
 *
 *			val3 = expr3;
 *			if (val == val3 || val == val2 || val == val1)
 *				x3 ();
 *				break; // gets auto added for the last clause (TODO test this)
 *
 *			// default
 *			xD ();
 *		} while (0)
 *
 *	Use a pre_switch so that the do_while can be lowered in the post_do.
 */
void Early_lower_control_flow::pre_switch(Switch* in, List<Statement*>* out)
{
	// val = expr;
	Variable *val = fresh_var ("TL");
	Assignment* assign = new Assignment (val, false, in->expr);
	out->push_back (new Eval_expr (assign));

	Do* _do = new Do (new List<Statement*>(), new BOOL (false));
	List<Variable*> *vars = new List<Variable*>;

	Switch_case* _default = NULL;

	// we need to know the header of the next block ahead of time
	for_lci (in->switch_cases, Switch_case, i)
	{
		if ((*i)->expr == NULL) // default
		{
			assert (_default == NULL);
			_default = *i;
		}
		else
		{
			// TODO if its a var, we dont need to extract it
			// val1 = expr1;
			Variable *_case = fresh_var ("TL");
			Assignment* assign = new Assignment (_case, false, (*i)->expr);
			_do->statements->push_back (new Eval_expr (assign));

			// (val == val1 || val == val2 || val == val3 || ... || val == valN)
			Bin_op* last = new Bin_op (
					val->clone (),
					new OP (new String ("==")),
					_case->clone ());

			for_lci (vars, Variable, v)
			{
				// val == valI
				Bin_op* current = new Bin_op (
					val->clone (),
					new OP (new String ("==")),
					(*v)->clone ());

				// (((val == val1) || ... || (val == val_i_-_1)) 
				//		|| (val == valI))
				last = new Bin_op (
					current,
					new OP (new String ("||")),
					last->clone ());
			}

			// if (...)
			If* _if = new If (
				last,
				(*i)->statements,
				new List<Statement*> ()); // empty else clause

			// store the var name for later if-clauses
			vars->push_back (_case);

			_do->statements->push_back(_if);
		}
	}

	// add the default statement at the end if its there
	if (_default) 
		_do->statements->push_back_all (_default->statements);

	out->push_back (_do);
}

