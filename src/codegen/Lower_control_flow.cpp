/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower any control flow statements into conditional
 * gotos, and add necessary labels.
 */

#include "Lower_control_flow.h"

/* Generate a new unique label */
AST_label* label ()
{
	static int count = 0;
	stringstream ss;
	ss << "L" << count;
	return new AST_label (new Token_label_name (new String (ss.str ())));
}

/* Return a new list of statements, containing a single statement
 * STATEMENT. */
List<AST_statement*>* wrap (AST_statement* statement)
{
	List<AST_statement*>* result = new List<AST_statement*> ();
	result->push_back (statement);
	return result;
}

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
Lower_control_flow::pre_if(AST_if* in, List<AST_statement*>* out)
{
	AST_label *l1 = label ();
	AST_label *l2 = label ();
	AST_label *l3 = label ();

	// create the gotos
	AST_goto *goto_l1 = new AST_goto (l1->label_name);
	AST_goto *goto_l2 = new AST_goto (l2->label_name);
	AST_goto *l1_goto_l3 = new AST_goto (l3->label_name);
	AST_goto *l2_goto_l3 = new AST_goto (l3->label_name);

	// fix the if statement
	List<AST_statement*>* iftrue = in->iftrue;
	List<AST_statement*>* iffalse = in->iffalse;
	// in->expr is unchanged
	in->iftrue = wrap (goto_l1);
	in->iffalse = wrap (goto_l2);

	// generate the code
	out->push_back (in);
	out->push_back (l1);
	out->push_back_all (iftrue);
	out->push_back (l1_goto_l3);
	out->push_back (l2);
	out->push_back_all (iffalse);
	out->push_back (l2_goto_l3);
	out->push_back (l3);
}

/* Convert
 *			while ($x) { y (); }
 * into
 *		L1:
 *			if ($x) nop ;
 *			else goto L2;
 *			y ();
 *			goto L1
 *		L2:
 */
void
Lower_control_flow::pre_while (AST_while* in, List<AST_statement*>* out)
{
	AST_label *l1 = label ();
	AST_label *l2 = label ();
	AST_goto *goto_l1 = new AST_goto (l1->label_name);
	AST_goto *goto_l2 = new AST_goto (l2->label_name);

	// create the if statement
	AST_if *if_stmt = new AST_if (in->expr, 
											wrap (new AST_nop ()), 
											wrap (goto_l2));

	// generate code
	out->push_back (l1);
	out->push_back (if_stmt);
	out->push_back_all (in->statements);
	out->push_back (goto_l1);
	out->push_back (l2);
}

/* Convert
 *		do { y (); } 
 *		while ($x)
 * into
 *		L1:
 *			y ();
 *			if ($x) goto L1:
 */
void
Lower_control_flow::pre_do (AST_do* in, List<AST_statement*>* out)
{
	AST_label* l1 = label ();
	AST_goto* goto_l1 = new AST_goto (l1->label_name);

	// make the if
	AST_if* if_stmt = new AST_if (in->expr, 
											wrap (goto_l1), 
											new List<AST_statement*> ());

	// generate the code
	out->push_back (l1);
	out->push_back_all (in->statements);
	out->push_back (if_stmt);
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
 *	which is then lowered by pre_while. */
void
Lower_control_flow::pre_for (AST_for* in, List<AST_statement*>* out)
{
	// push back the initializer
	out->push_back (dynamic_cast<AST_statement*>(in->init));

	// Add the increment statement to the loop body
	in->statements->push_back (dynamic_cast<AST_statement*>(in->incr));

	// create the while
	AST_while *while_stmt = new AST_while (in->cond, in->statements);

	// lower the while
	out->push_back_all (transform_statement (while_stmt));
}

void 
Lower_control_flow::pre_foreach(AST_foreach* in, List<AST_statement*>* out)
{
}


void 
Lower_control_flow::pre_switch(AST_switch* in, List<AST_statement*>* out)
{
}


void 
Lower_control_flow::pre_switch_case(AST_switch_case* in, List<AST_switch_case*>* out)
{
}


void 
Lower_control_flow::pre_break(AST_break* in, List<AST_statement*>* out)
{
}


void 
Lower_control_flow::pre_continue(AST_continue* in, List<AST_statement*>* out)
{
}


void 
Lower_control_flow::pre_try(AST_try* in, List<AST_statement*>* out)
{
}


void 
Lower_control_flow::pre_catch(AST_catch* in, List<AST_catch*>* out)
{
}


void 
Lower_control_flow::pre_throw(AST_throw* in, List<AST_statement*>* out)
{
}


AST_expr*
Lower_control_flow::pre_conditional_expr(AST_conditional_expr* in)
{
}

