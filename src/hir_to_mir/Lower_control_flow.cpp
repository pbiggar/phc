/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower any control flow statements into conditional
 * gotos, and add necessary labels.
 */

// TODO we have to handle iterators too: 
//   http://www.php.net/manual/en/ref.spl.php
//   http://ramikayyali.com/archives/2005/02/25/iterators


#include <sstream>

#include "lib/Vector.h"

#include "Lower_control_flow.h"
#include "HIR_to_MIR.h"
#include "process_ir/General.h"

using namespace HIR;
using namespace std;

template <class T>
const char* get_attr_name ()
{
	if (T::ID == Break::ID) return "phc.codegen.break_label";
	if (T::ID == Continue::ID) return "phc.codegen.continue_label";
	return NULL;
}

void clear_attrs (Node* in)
{
	in->attrs->erase ("phc.codegen.break_label");
	in->attrs->erase ("phc.codegen.continue_label");
}

/* We increase the depth for any statement which works with break and continue.
 * We decrease it on the way back up. The labels are created by post_break,
 * stored in the labels stack, and used as necessary. */
template <class T>
void Lower_control_flow::add_label (Node* in, Statement_list *out)
{
	assert (break_levels.back () == in);
	assert (continue_levels.back () == in);

	// Not a great way to do this, sorry.
	const char* attr_name = get_attr_name<T> ();
	if (!in->attrs->has (attr_name))
		return;

	MIR::Label* label = dyc<MIR::Label> (in->attrs->get (attr_name));
	out->push_back (new FOREIGN (label->clone ()));
}

template <class T>
MIR::Label*
Lower_control_flow::get_label (Node* in)
{
	assert (break_levels.back () == in);
	assert (continue_levels.back () == in);

	// Not a great way to do this, sorry.
	const char* attr_name = get_attr_name<T> ();
	if (!in->attrs->has (attr_name))
		return NULL;

	return dyc<MIR::Label> (in->attrs->get (attr_name));
}

// Get IN's exit label, or create one for it, and return it.
template <class T>
MIR::Label* Lower_control_flow::exit_label (Node* in)
{
	const char* attr_name = get_attr_name <T> ();
	if (in->attrs->has (attr_name))
	{
		MIR::Label *label = dynamic_cast <MIR::Label*> (in->attrs->get (attr_name));
		assert (label);
		return label;
	}

	MIR::Label *label = MIR::fresh_label ();
	in->attrs->set (attr_name, label);
	return label;
}

MIR::VARIABLE_NAME* Lower_control_flow::fold_var (VARIABLE_NAME* in)
{
	return folder.fold_variable_name (in);
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
void Lower_control_flow::lower_if(If* in, Statement_list* out)
{
	// Don't lower them if they're already lowered
	MIR::Label *l1 = MIR::fresh_label ();
	MIR::Label *l2 = MIR::fresh_label ();
	MIR::Label *l3 = MIR::fresh_label ();

	// create the gotos
	MIR::Goto *l1_goto_l3 = new MIR::Goto (l3->label_name->clone ());
	MIR::Goto *l2_goto_l3 = new MIR::Goto (l3->label_name->clone ());

	// make the if
	MIR::Branch *branch = new MIR::Branch (
		fold_var (in->variable_name), 
		l1->label_name->clone (), 
		l2->label_name->clone ());

	// generate the code
	out->push_back (new FOREIGN (branch));
	out->push_back (new FOREIGN (l1));
	out->push_back_all (in->iftrue);
	out->push_back (new FOREIGN (l1_goto_l3));
	out->push_back (new FOREIGN (l2));
	out->push_back_all (in->iffalse);
	out->push_back (new FOREIGN (l2_goto_l3));
	out->push_back (new FOREIGN (l3));
}

void Lower_control_flow::post_if(If* in, Statement_list* out)
{
	lower_if (in, out);
}

/* Convert
 *			while ($x) { y (); }
 * into
 *		L0:
 *			y ();
 *			goto L0
 */

void Lower_control_flow::lower_loop (Loop* in, Statement_list* out)
{
	MIR::Label *l0 = MIR::fresh_label ();
	MIR::Goto *goto_l0 = new MIR::Goto (l0->label_name->clone ());

	// generate code
	out->push_back (new FOREIGN (l0));
	out->push_back_all (in->statements);
	out->push_back (new FOREIGN (goto_l0));
}

void Lower_control_flow::post_loop (Loop* in, Statement_list* out)
{
	add_label<Continue> (in, out);
	lower_loop (in, out);
	add_label<Break> (in, out);
	break_levels.pop_back ();
	continue_levels.pop_back ();
	clear_attrs (in);
}

/* Convert 
 *   foreach ($arr as $key => $value)
 *   {
 *		 ...;
 *   }
 * into
 *			if (!is_array ($arr)) 
 *			{
 *				if (!is_object ($arr))
 *				{
 *					trigger_error (\"Invalid argument supplied for foreach()\", E_USER_WARNING);"
 *					goto L4;
 *				}
 *
 *				$arr = (array)($arr);
 *			}
 *			foreach_reset ($arr, iter); 
 *		L0:
 *			$T = foreach_has_key ($arr, iter);
 *			if ($T) goto L1; else goto L2;
 *		L1:
 *			$key = foreach_get_key ($arr, iter); // optional 
 *			$val = foreach_get_val ($arr, iter);
 *			....  
 *		L3: // continues to here
 *			foreach_next ($arr, iter); 
 *			goto L0:
 *		L2: // breaks jump here
 *			foreach_end ($arr, iter);
 *		L4:
 */

void Lower_control_flow::lower_foreach (Foreach* in, Statement_list* out)
{
	/* We wrap a number of MIR nodes in foreign, but we need to convert some of
	 * them first. */
	HIR::VARIABLE_NAME* cast_array_name = fresh_var_name ("LF");
	MIR::VARIABLE_NAME* array_name = fold_var (cast_array_name); // keep the attributes

	(*out
		<< "if (!is_array ($" << in->arr << "))"
		<< "{"
		<< "	if (!is_object ($" << in->arr << "))"
		<< "	{"
		<< "		trigger_error (\"Invalid argument supplied for foreach()\", E_USER_WARNING);"
		<< "		PHC_XXX();" // a goto will be added here
		<< "	}"
		<<	"	else"
		<< "		$" << cast_array_name << " = (array)($" << in->arr << ");"
		<< "}"
		<< "else"
		<< "{"
		<< "	$" << cast_array_name << " =" << (in->is_ref ? "&" : "") << " $" << in->arr << ";"
		<< "}"
	).to_pass (s("HIR-to-MIR"), in);


	// foreach_reset ($arr, iter); 
	MIR::HT_ITERATOR* iter = MIR::fresh_iter ();
	out->push_back (new FOREIGN (
		new MIR::Foreach_reset (array_name->clone (), iter)));


	// L0:
	MIR::Label* l0 = MIR::fresh_label ();
	out->push_back (new FOREIGN (l0));

	// $T = foreach_has_key ($arr, iter);
	VARIABLE_NAME* has_key = fresh_var_name ("THK");
	out->push_back (
		new Assign_var (
			has_key,
			false,
			new FOREIGN (
				new MIR::Foreach_has_key (
					array_name->clone (),
					iter->clone ()))));


	// if ($T) goto L1; else goto L2;
	MIR::Label* l1 = MIR::fresh_label ();
	MIR::Label* l2 = get_label<Break> (in);
	if (l2 == NULL) l2 = MIR::fresh_label ();

	out->push_back (new FOREIGN (
		new MIR::Branch (
			fold_var (has_key),
			l1->label_name->clone (), 
			l2->label_name->clone ())));


	// L1:
	out->push_back (new FOREIGN (l1));


	// $key = foreach_get_key ($arr, iter); 
	MIR::Foreach_get_key* get_key = new MIR::Foreach_get_key (
		array_name->clone (),
		iter->clone ());

	VARIABLE_NAME* key = in->key;
	if (key == NULL)
		key = fresh_var_name ("LCF_KEY_");

	out->push_back (
			new Assign_var (
				key,
				new FOREIGN (get_key)));
	

	out->push_back (
		new Assign_var(
			in->val->clone (),
			in->is_ref,
			new FOREIGN (
				new MIR::Foreach_get_val (
					array_name->clone (),
					iter->clone ()))));


	// ....  
	out->push_back_all (in->statements);


	// L3: // continues jump to here
	add_label<Continue> (in, out);


	// foreach_next ($arr, iter); 
	out->push_back (new FOREIGN (
			new MIR::Foreach_next (
				array_name->clone (),
				iter->clone ())));

	// goto L0:
	out->push_back (new FOREIGN (new MIR::Goto (l0->label_name->clone ())));


	// L2:
	out->push_back (new FOREIGN (l2)); // continues jump to here


	// foreach_end ($arr, iter);
	out->push_back (new FOREIGN (
		new MIR::Foreach_end (
			array_name->clone (),
			iter->clone ())));

	// L4:
	MIR::Label* l4 = MIR::fresh_label ();
	out->push_back (new FOREIGN (l4)); // scalars jump to here

	// HACK: Because we couldnt put a goto in the parsed code above, we put in a
	// marker PHC_XXX(). We'll replace that with a goto now.
	foreach (HIR::Statement*& stmt, *out)
	{
		if (stmt->match (new Eval_expr (new HIR::Method_invocation (NULL, new METHOD_NAME ("PHC_XXX"), new HIR::Actual_parameter_list))))
		{
			stmt = new FOREIGN (new MIR::Goto (l4->label_name->clone ()));
			break;
		}
	}

	// wrap it in a PHP script to call visit
	(new PHP_script (out))->visit (new Clone_blank_mixins<Node, Visitor> (in, new Node_list)); // TODO we should have nodes here
}

void Lower_control_flow::post_foreach(Foreach* in, Statement_list* out)
{
	lower_foreach (in, out);
	// we add the break and continue labels in lower_foreach
	break_levels.pop_back ();
	continue_levels.pop_back ();
	clear_attrs (in);
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
// TODO: what about 'break "my_string" (and then break '17')?
// TODO: FYI: Objects/strings evaluate to 0
template <class T>
void Lower_control_flow::lower_exit (T* in, Statement_list* out)
{
	Vector<Node*> *levels;
	if (Break::ID == in->ID) levels = &break_levels;
	if (Continue::ID == in->ID) levels = &continue_levels;
	assert (levels);
	int num_levels = (int)(levels->size ());


	int error_depth;
	// 'break', 'break 1', and all coefficients < 1 are all the same. 
	INT *_int = dynamic_cast<INT*> (in->expr);
	if (in->expr == NULL || (_int && _int->value <= 1))
	{
		error_depth = 1;
		in->expr = new INT (1);
		in->expr->clone_mixin_from (in);
	}
	else if (_int)
		error_depth = _int->value;
	else
		error_depth = -1; // we don't know


	// Check that we arent being asked to jump further than we know
	// we can go
	if (error_depth > num_levels || num_levels == 0)
	{
		// find a good node to put the error on
		Node* error_node = in->expr;
		if (error_node == NULL)
			error_node = in;

		if (error_depth == -1)
			error_depth = 1; // TODO need a better error message

		phc_error ("Cannot break/continue %d levels", error_node, error_depth);
	}

	// if we survived, we expect there to be a target
	assert (num_levels);


	if (error_depth != -1) // We know exactly where we're jumping to
	{
		// Create a label, pushback a goto to it, and attach it as an attribute
		// of the appropriate looping construct.
		Node* level = (*levels)[num_levels - error_depth];
		out->push_back (new FOREIGN (
			new MIR::Goto ((exit_label<T> (level))->label_name->clone ())));
	}
	else
	{
		// Otherwise we create a label and a goto for each possible loop, and attach
		// the label to the goto.
		//
		// $TB1 = $x;
		VARIABLE_NAME* lhs = fresh_var_name ("TB");
		out->push_back (
			new Assign_var (
				lhs,
				in->expr));

		// 1 branch and label per level:
		//		if ($TB1 = 1) goto L1; else goto L2;
		//	L2:
		Vector<Node*>::reverse_iterator i;
		int depth;
		for (i = levels->rbegin (), depth = 1; i != levels->rend (); i++, depth++)
		{
			// We break to depth 1 for any expr <= 1
			OP* op = new OP (new String ("=="));
			if (depth == 1)
				op = new OP (new String ("<="));

			//	if ($TB1 == depth) goto L1; else goto L2;
			MIR::Label* iffalse = MIR::fresh_label ();
			push_back_pieces ( // push the pieces from the eval_var back
				new FOREIGN (
					new MIR::Branch (
						(fold_var (eval (
							new Bin_op (
								lhs->clone(),
								op,
								eval (new INT (depth)))))),
						exit_label<T> (*i)->label_name, // get the label from this depth
						iffalse->label_name->clone ())),
				out);

			//	L2:
			out->push_back (new FOREIGN (iffalse));
		}
		assert (depth == num_levels + 1);

		// Print an error, and die with 255
		(*out
			<<	"echo (\"\nFatal error: Cannot break/continue $"
			<< lhs
			<< " levels in " << in->get_filename ()
			<< " on line " << in->get_line_number () << "\n\");\n"
			<< "die (255);"
		).finish (in);

	}
}

void Lower_control_flow::post_break (Break* in, Statement_list* out)
{
	lower_exit<Break> (in, out);
}

void Lower_control_flow::post_continue (Continue* in, Statement_list* out)
{
	lower_exit<Continue> (in, out);
}


void Lower_control_flow::pre_control_flow (Statement* in, Statement_list* out)
{
	break_levels.push_back (in);
	continue_levels.push_back (in);
	out->push_back (in);
}


void Lower_control_flow::pre_loop(Loop* in, Statement_list* out)
{
	pre_control_flow (in, out);
}

void Lower_control_flow::pre_foreach(Foreach* in, Statement_list* out)
{
	pre_control_flow (in, out);
}
