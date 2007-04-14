/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower any control flow statements into conditional
 * gotos, and add necessary labels.
 */

#include "Lower_control_flow.h"
#include "process_ast/XML_unparser.h"

/* Generate a new unique label */
AST_label* label ()
{
	static int count = 0;
	stringstream ss;
	ss << "L" << count;
	count ++;
	return new AST_label (new Token_label_name (new String (ss.str ())));
}

/* Add a comment, generated from DESC and OWNER to NEW */
#if 0
void
add_comment (AST_commented_node* new_node, const char* desc, AST_node* owner)
{
	static int comment_number = 0;

	// get a number for the lowered object
	const char* name = "phc.lowering.number";
	int number;
	if (owner->attrs->has (name))
		number = owner->attrs->get_integer (name)->value ();
	else
	{
		number = comment_number;
		comment_number ++;
		owner->attrs->set (name, new Integer (number));
	}

	stringstream ss;
	ss << desc << number;
	String* comment = new String (ss.str ());
//	new_node->attrs->attrs->set(
//										 "phc.unparser.comment.after",
//										 new Boolean(true));
//	new_node->attrs->set("phc.comments", new List<String*> (comment));
}
#endif

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
Lower_control_flow::post_if(AST_if* in, List<AST_statement*>* out)
{
	// Don't lower them if they're already lowered
	// TODO this would be easier if there was a new catagory of if
	AST_label *l1 = label ();
	AST_label *l2 = label ();
	AST_label *l3 = label ();

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
	AST_label *l0 = label ();
	AST_label *l1 = label ();
	AST_label *l2 = label ();
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
	AST_label* l1 = label ();
	AST_label* l2 = label ();

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
 * want to go down that road. So we'll convert this to nested if's.
 *
 * Convert
 *		switch (expr)
 *		{
 *			case expr1:
 *				x1 ();
 *			case expr2:
 *				x2 ();
 *			...
 *			default exprD:
 *				xD ();
 *		}
 *
 *	into
 *		val = expr;
 *		if (expr == expr1) goto L1
 *		else if (expr == expr2) goto L2
 *		...
 *		else goto
 * TODO finish this
 *			
 */	
void 
Lower_control_flow::post_switch(AST_switch* in, List<AST_statement*>* out)
{
	out->push_back (in);
}


void 
Lower_control_flow::post_switch_case(AST_switch_case* in, List<AST_switch_case*>* out)
{
	out->push_back (in);
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
