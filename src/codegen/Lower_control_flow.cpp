/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower any control flow statements into conditional
 * gotos, and add necessary labels.
 */

/* We increase the depth for any statement which works with break and continue.
 * We decrease it on the way back up. The labels are created by post_break,
 * stored in the labels stack, and used as necessary. */

#include "Lower_control_flow.h"
#include "fresh.h"
#include <sstream>
#include "process_ast/XML_unparser.h"

// TODO if obfuscate is set, we should randomly rearrange the basic blocks

#define BREAK_ATTR "phc.codegen.break_label"
#define CONTINUE_ATTR "phc.codegen.continue_label"
template <class T>
const char* get_attr_name ()
{
	if (T::ID == AST_break::ID) return BREAK_ATTR;
	if (T::ID == AST_continue::ID) return CONTINUE_ATTR;
	return NULL;
}


template<class T> 
void Lower_control_flow::potentially_add_label (AST_node* in, List<AST_statement*> *out)
{
	assert (break_levels.back () == in);
	assert (continue_levels.back () == in);

	// Not a great way to do this, sorry.
	const char* attr_name = get_attr_name<T> ();
	if (!in->attrs->has (attr_name))
		return;

	AST_label* label = dynamic_cast<AST_label*> (in->attrs->get (attr_name));
	assert (label != NULL);
	out->push_back (label);
}

// Returns true if IN is a Toekn_int with a value of VALUE.
bool is_int (AST_expr* in, int value)
{
	Token_int* _int = dynamic_cast<Token_int*> (in);
	return _int && _int->value == value;
}

String* string_for_int (int i)
{
	stringstream ss;
	ss << i;
	return new String (ss.str ());
}

// Get IN's exit label, or create one for it, and return it.
template <class T>
AST_label* Lower_control_flow::exit_label (AST_node* in)
{
	const char* attr_name = get_attr_name <T> ();
	if (in->attrs->has (attr_name))
	{
		AST_label *label = dynamic_cast <AST_label*> (in->attrs->get (attr_name));
		assert (label);
		return label;
	}

	AST_label *label = fresh_label ();
	in->attrs->set (attr_name, label);
	return label;
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
lower_if(AST_if* in, List<AST_statement*>* out)
{
	// Don't lower them if they're already lowered
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

void
Lower_control_flow::post_if(AST_if* in, List<AST_statement*>* out)
{
	lower_if (in, out);
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

void lower_while (AST_while* in, List<AST_statement*>* out)
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

void
Lower_control_flow::post_while (AST_while* in, List<AST_statement*>* out)
{
	potentially_add_label<AST_continue> (in, out);
	lower_while (in, out);
	potentially_add_label<AST_break> (in, out);
	break_levels.pop_back ();
	continue_levels.pop_back ();
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
lower_do (AST_do* in, List<AST_statement*>* out)
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

void Lower_control_flow::post_do (AST_do* in, List<AST_statement*>* out)
{
	potentially_add_label<AST_continue> (in, out);
	lower_do (in, out);
	potentially_add_label<AST_break> (in, out);
	break_levels.pop_back ();
	continue_levels.pop_back ();
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
Lower_control_flow::lower_for (AST_for* in, List<AST_statement*>* out)
{
	// these are expressions, which arent statements, so they need to be wrapped
	AST_statement* init = new AST_eval_expr (in->init);
	AST_statement* incr = new AST_eval_expr (in->incr);

	if (in->cond == NULL) 
		in->cond = new Token_bool (true, new String ("true"));

	// create the while
	AST_while *while_stmt = new AST_while (in->cond, in->statements);

	// A continue in a for loop lands just before the increment
	potentially_add_label<AST_continue> (in, while_stmt->statements);
	while_stmt->statements->push_back (incr);

	// push it all back
	out->push_back (init);
	lower_while (while_stmt, out);
}
void
Lower_control_flow::post_for (AST_for* in, List<AST_statement*>* out)
{
	lower_for (in, out);
	potentially_add_label<AST_break> (in, out);
	break_levels.pop_back ();
	continue_levels.pop_back ();
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
	potentially_add_label<AST_continue> (in, out);
	out->push_back (in);
	potentially_add_label<AST_break> (in, out);
	break_levels.pop_back ();
	continue_levels.pop_back ();
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
 *		if (expr == expr1) goto L1; else goto N1;
 *	N1:
 *		if (expr == expr2) goto L2; else goto N2;
 *	N2:
 *		if (expr == expr3) goto L3; else goto N3;
 *	N3:
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
lower_switch(AST_switch* in, List<AST_statement*>* out)
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
			// the else branch just goes to the next line. We dont allow NULL else
			// statements (perhaps we should?).
			AST_label* next = fresh_label ();

			// make the comparison
			Token_op* op = new Token_op (new String ("=="));
			AST_expr* compare = new AST_bin_op (lhs->clone (), op, (*i)->expr);
			AST_branch* branch = new AST_branch (compare, header->label_name, next->label_name);

			branches->push_back (branch);
			branches->push_back (next);
		}

		blocks->push_back (header);
		blocks->push_back_all ((*i)->statements);
		blocks->push_back (new AST_goto (next_block_header->label_name)); // fallthrough
	}
	blocks->push_back (next_block_header);

	if (_default) 
		branches->push_back (_default);
	else // if default is blank jump to the end
		branches->push_back (new AST_goto (next_block_header->label_name));

	out->push_back_all (branches);
	out->push_back_all (blocks);
}

void 
Lower_control_flow::post_switch(AST_switch* in, List<AST_statement*>* out)
{
	lower_switch (in, out);
	// A continue is the same as a break, so add the label at the same place
	potentially_add_label<AST_continue> (in, out);
	potentially_add_label<AST_break> (in, out);
	break_levels.pop_back ();
	continue_levels.pop_back ();
}

/* Transform:
 *		break $x;
 *	into:
 *		$TB1 = $x;
 *		if ($TB1 = 1) goto L1; else goto L2;
 *	L2:
 *		if ($TB1 = 2) goto L3; else goto L4;
 *	L4:
 *		if ($TB1 = 3) goto L5; else goto L6;
 *	L6:
 *		if ($TB1 = 4) goto L7; else goto L8;
 *	L8:
 *
 *	where L(2n) is the label at the end of the nth inner loop construct
 */
void 
Lower_control_flow::post_break (AST_break* in, List<AST_statement*>* out)
{
	lower_exit<AST_break> (in, out);
}
void 
Lower_control_flow::post_continue (AST_continue* in, List<AST_statement*>* out)
{
	lower_exit<AST_continue> (in, out);
}

template <class T>
void Lower_control_flow::lower_exit (T* in, List<AST_statement*>* out)
{
	/* If this break has a NULL expression, it's much easier (and gives more
	 * readable output) if we special case it. Also, break 0 is the same as
	 * break 1, which is the same as just break. Its easier to handle it all
	 * together. */
	List<AST_node*> *levels; // It gets uglier
	if (AST_break::ID == in->ID) levels = &break_levels;
	if (AST_continue::ID == in->ID) levels = &continue_levels;
	assert (levels);

	// TODO: matching doesnt seem to work here
	if (in->expr == NULL || is_int (in->expr, 0) || is_int (in->expr, 1))
	{
		// Create a label, pushback a goto to it, and attach it as an attribute
		// of the innermost looping construct.
		AST_node* level = levels->back ();

		AST_label *target = exit_label<T> (level);
		AST_goto *exit = new AST_goto (target->label_name);
		out->push_back (exit);
		return;
	}

	// Otherwise we create a label and a goto for each possible loop, and attach
	// the label it the loop.
	
	// Since we compare to the expression, we need to create a variable for it.
	AST_variable *lhs = fresh_var ("TB");
	AST_assignment* assign = new AST_assignment (lhs, false, in->expr);
	out->push_back (new AST_eval_expr (assign));

	// 1 branch and label per level:
	//		if ($TB1 = 1) goto L1; else goto L2;
	//	L2:
	List<AST_node*>::reverse_iterator i;
	unsigned int depth = 1;
	for (i = levels->rbegin (); i != levels->rend (); i++)
	{
		// FYI: Objects/strings evaluate to 0
		AST_node* level = (*i);

		// Attach the break target to the loop construct.
		AST_label* iftrue = exit_label<T> (level);

		// Create: if ($TB1 == depth)
		Token_op* op = new Token_op (new String ("=="));
		Token_int* branch_num = new Token_int (depth, string_for_int (depth));
		AST_expr* compare = new AST_bin_op (lhs->clone (), op, branch_num);

		// Zero is the same as one, so check for it too
		if (depth == 1)
		{
			// Turn ($TB == 1) into ($TB == 0 || $TB == 1)
			Token_op* eq_op = new Token_op (new String ("=="));
			Token_int* zero = new Token_int (0, new String ("0"));
			AST_expr* zero_comp = new AST_bin_op (lhs->clone (), eq_op, zero);

			Token_op* or_op = new Token_op (new String ("||"));
			compare = new AST_bin_op (compare, or_op, zero_comp);
		}

		AST_label* iffalse = fresh_label ();
		AST_branch* branch = new AST_branch (compare, iftrue->label_name, iffalse->label_name);

		out->push_back (branch);
		out->push_back (iffalse);
		depth ++;
	}
	assert (depth == break_levels.size () + 1);

	// Add a failure condition if the user tries to break too far
	// TODO: Not exactly what we'd expect, but a decent first attempt
	AST_method_name* name = new Token_method_name (new String ("die"));
	List<AST_actual_parameter*> *params = new List<AST_actual_parameter*> ();
	String* error_string = 
		new String ("Fatal error: Too many break/continue levels");
	AST_actual_parameter* param = 
		new AST_actual_parameter (false, new Token_string (error_string, error_string));
	params->push_back (param);
	Token_class_name *stdlib = new Token_class_name (new String ("%STDLIB%"));
	out->push_back (new AST_eval_expr (new AST_method_invocation (stdlib, name, params)));
}


void Lower_control_flow::pre_while(AST_while* in, List<AST_statement*>* out)
{
	break_levels.push_back (in);
	continue_levels.push_back (in);
	out->push_back (in);
}

void Lower_control_flow::pre_do(AST_do* in, List<AST_statement*>* out)
{
	break_levels.push_back (in);
	continue_levels.push_back (in);
	out->push_back (in);
}

void Lower_control_flow::pre_for(AST_for* in, List<AST_statement*>* out)
{
	break_levels.push_back (in);
	continue_levels.push_back (in);
	out->push_back (in);
}

void Lower_control_flow::pre_foreach(AST_foreach* in, List<AST_statement*>* out)
{
	break_levels.push_back (in);
	continue_levels.push_back (in);
	out->push_back (in);
}

void Lower_control_flow::pre_switch(AST_switch* in, List<AST_statement*>* out)
{
	break_levels.push_back (in);
	continue_levels.push_back (in);
	out->push_back (in);
}
