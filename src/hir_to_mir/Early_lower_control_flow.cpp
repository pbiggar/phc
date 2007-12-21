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
