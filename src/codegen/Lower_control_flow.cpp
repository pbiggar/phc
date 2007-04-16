/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower any control flow statements into conditional
 * gotos, and add necessary labels.
 */

#include "Lower_control_flow.h"
#include "fresh.h"
#include "process_ast/XML_unparser.h"

/* Convert
 *			if ($x) { y (); }
 *			else { z (); }
 * into
 *			if ($x) goto L1;
 *			else goto L2;
 *		L1:
 *			y ();
 *			goto L3;
 *		L2:
 *			z ();
 *			goto L3;
 *		L3:
 *
 * We only need two labels, since the first edge can be an implict
 * fall-through edge if we negate the condition, but this is more
 * readable and understandable, as it keeps the structure of the original
 * if-else statement. */
void
Lower_control_flow::post_if(AST_if* in, List<AST_statement*>* out)
{
	// Don't lower them if they're already lowered
	// TODO this would be easier if there was a new catagory of if
	AST_label *l1 = fresh_label ();
	AST_label *l2 = fresh_label ();
	AST_label *l3 = fresh_label ();

	// create the gotos
	AST_goto *l1_goto_l3 = new AST_goto (l3->label_name);
	AST_goto *l2_goto_l3 = new AST_goto (l3->label_name);

	// make the if
	AST_branch *branch = new AST_branch (in->expr, l1->label_name, l2->label_name);

	// generate the code
	out->push_back (branch);
	out->push_back (l1);
	out->push_back_all (in->iftrue);
	out->push_back (l1_goto_l3);
	out->push_back (l2);
	out->push_back_all (in->iffalse);
	out->push_back (l2_goto_l3);
	out->push_back (l3);
}

/* Convert
 *			while ($x) { y (); }
 * into
 *		L0:
 *			if ($x) goto L1;
 *			else goto L2;
 *		L1:
 *			y ();
 *			goto L0
 *		L2:
 */
void
Lower_control_flow::post_while (AST_while* in, List<AST_statement*>* out)
{
	AST_label *l0 = fresh_label ();
	AST_label *l1 = fresh_label ();
	AST_label *l2 = fresh_label ();
	AST_goto *goto_l0 = new AST_goto (l0->label_name);

	// create the if statement
	AST_branch *branch = new AST_branch (in->expr, l1->label_name, l2->label_name);

	// generate code
	out->push_back (l0);
	out->push_back (branch);
	out->push_back (l1);
	out->push_back_all (in->statements);
	out->push_back (goto_l0);
	out->push_back (l2);
}

/* Convert
 *		do { y (); } 
 *		while ($x)
 * into
 *		L1:
 *			y ();
 *			if ($x) goto L1:
 *			else goto L2:
 *		L2:
 */
void
Lower_control_flow::post_do (AST_do* in, List<AST_statement*>* out)
{
	AST_label* l1 = fresh_label ();
	AST_label* l2 = fresh_label ();

	// make the if
	AST_branch* branch = new AST_branch (in->expr, l1->label_name, l2->label_name);

	// generate the code
	out->push_back (l1);
	out->push_back_all (in->statements);
	out->push_back (branch);
	out->push_back (l2);
}

/* Convert
 *			for (i = 0; i < N; i++) y ();
 * into
 *			i = 0;
 *		L1
 *			if (i < N) nop
 *			else goto L2
 *			y ();
 *			i++;
 *			goto L2
 *		L2
 *
 * This is done by converting into
 *			i = 0
 *			while (i < N)
 *			{
 *				y ();
 *				i++;
 *			}
 *	which is then lowered by post_while. */
void
Lower_control_flow::post_for (AST_for* in, List<AST_statement*>* out)
{
	// these are expressions, which arent statements, so they need to be wrapped
	AST_statement* init = new AST_eval_expr (in->init);
	AST_statement* incr = new AST_eval_expr (in->incr);

	if (in->cond == NULL) in->cond = new Token_null (new String ("null"));

	// create the while
	AST_while *while_stmt = new AST_while (in->cond, in->statements);
	while_stmt->statements->push_back (incr);
	List<AST_statement*> *lowered_while = transform_statement (while_stmt);

	// push it all back
	out->push_back (init);
	out->push_back_all (lowered_while);
}

/* Foreach looks complicated. Theoretically, you could replace it with
 *		reset ($array)
 *		while (current ($array))
 *		{
 *			$x = current ($array);
 *			...
 *			next ($array);
 *		}
 * but it seems from looking at the PHP opcodes that the internal iterator
 * (why?!?) needs locks acquired, which makes sense. I'll return to this later
 * */
void 
Lower_control_flow::post_foreach(AST_foreach* in, List<AST_statement*>* out)
{
	out->push_back (in);
}

/* Switch is a little complicated aswell. In theory, it would be nice to
 * convert this to a jump table in the generated code, but we can't really do
 * that with the C output. We could use GCC extensions, but we probably dont
 * want to go down that road. So we'll convert this to simple if's.
 *
 * Note that the blocks always fall-through. We will rely on a break
 * transform to escape the blocks.
 *
 * These need to e separated since the default must be after the last
 * comparison, but must fall through in the specified order.
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
 *		if (expr == expr1) goto L1;
 *		if (expr == expr2) goto L2;
 *		if (expr == expr3) goto L3;
 *		goto LD;
 *	L1:
 *		x1 ();
 *		goto L2;
 *	L2:
 *		x2 ();
 *		break; // to become goto LE
 *		goto LD;
 *	LD:
 *		xD ();
 *		goto L3;
 *	L3:
 *		x3 ();
 *		goto LE:
 *	LE:
 *
 */	
void 
Lower_control_flow::post_switch(AST_switch* in, List<AST_statement*>* out)
{
	// val = expr;
	AST_variable *lhs = fresh_var ("TL");
	AST_assignment* assign = new AST_assignment (lhs, false, in->expr);
	out->push_back (new AST_eval_expr (assign));

	List<AST_statement*> *branches = new List<AST_statement*> ();
	List<AST_statement*> *blocks = new List<AST_statement*> ();

	List<AST_switch_case*> *cases = in->switch_cases;
	List<AST_switch_case*>::const_iterator i;

	// we need to know the header of the next block ahead of time
	AST_label* next_block_header = fresh_label ();
	AST_goto* _default = NULL;
	for (i = cases->begin (); i != cases->end (); i++)
	{
		AST_label* header = next_block_header;
		next_block_header = fresh_label ();

		if ((*i)->expr == NULL) // default
		{
			assert (_default == NULL);
			_default = new AST_goto (header->label_name);
		}
		else
		{
			// make the comparison
			Token_op* op = new Token_op (new String ("=="));
			AST_expr* compare = new AST_bin_op (lhs->clone (), op, (*i)->expr);
			AST_branch* branch = new AST_branch (compare, header->label_name, NULL);
			branches->push_back (branch);
		}

		blocks->push_back (header);
		blocks->push_back_all ((*i)->statements);
		blocks->push_back (new AST_goto (next_block_header->label_name)); // fallthrough
	}
	blocks->push_back (next_block_header);

	if (_default) 
		branches->push_back (_default);

	out->push_back_all (branches);
	out->push_back_all (blocks);
}

void 
Lower_control_flow::post_break(AST_break* in, List<AST_statement*>* out)
{
	out->push_back (in);
}


void 
Lower_control_flow::post_continue(AST_continue* in, List<AST_statement*>* out)
{
	out->push_back (in);
}


void 
Lower_control_flow::post_try(AST_try* in, List<AST_statement*>* out)
{
	out->push_back (in);
}


void 
Lower_control_flow::post_catch(AST_catch* in, List<AST_catch*>* out)
{
	out->push_back (in);
}


void 
Lower_control_flow::post_throw(AST_throw* in, List<AST_statement*>* out)
{
	out->push_back (in);
}
