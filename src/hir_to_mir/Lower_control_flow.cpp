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

// TODO we have to handle iterators too: 
//   http://www.php.net/manual/en/ref.spl.php
//   http://ramikayyali.com/archives/2005/02/25/iterators

#include "Lower_control_flow.h"
#include "process_ir/fresh.h"
#include "process_ir/General.h"
#include <sstream>
#include <vector>

using namespace HIR;

template <class T>
const char* get_attr_name ()
{
	if (T::ID == Break::ID) return "phc.codegen.break_label";
	if (T::ID == Continue::ID) return "phc.codegen.continue_label";
	return NULL;
}

template<class T> 
void Lower_control_flow::add_label (Node* in, List<Statement*> *out)
{
	assert (break_levels.back () == in);
	assert (continue_levels.back () == in);

	// Not a great way to do this, sorry.
	const char* attr_name = get_attr_name<T> ();
	if (!in->attrs->has (attr_name))
		return;

	Label* label = dynamic_cast<Label*> (in->attrs->get (attr_name));
	assert (label != NULL);
	out->push_back (label->clone ());
}

// Get IN's exit label, or create one for it, and return it.
template <class T>
Label* Lower_control_flow::exit_label (Node* in)
{
	const char* attr_name = get_attr_name <T> ();
	if (in->attrs->has (attr_name))
	{
		Label *label = dynamic_cast <Label*> (in->attrs->get (attr_name));
		assert (label);
		return label;
	}

	Label *label = fresh_label ();
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
void Lower_control_flow::lower_if(If* in, List<Statement*>* out)
{
	// Don't lower them if they're already lowered
	Label *l1 = fresh_label ();
	Label *l2 = fresh_label ();
	Label *l3 = fresh_label ();

	// create the gotos
	Goto *l1_goto_l3 = new Goto (l3->label_name->clone ());
	Goto *l2_goto_l3 = new Goto (l3->label_name->clone ());

	// make the if
	Branch *branch = new Branch (in->expr, l1->label_name->clone (), l2->label_name->clone ());

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

void Lower_control_flow::post_if(If* in, List<Statement*>* out)
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

void Lower_control_flow::lower_loop (Loop* in, List<Statement*>* out)
{
	Label *l0 = fresh_label ();
	Goto *goto_l0 = new Goto (l0->label_name->clone ());

	// generate code
	out->push_back (l0);
	out->push_back_all (in->statements);
	out->push_back (goto_l0);
}

void Lower_control_flow::post_loop (Loop* in, List<Statement*>* out)
{
	add_label<Continue> (in, out);
	lower_loop (in, out);
	add_label<Break> (in, out);
	break_levels.pop_back ();
	continue_levels.pop_back ();
}

/* Convert 
 *   foreach (expr() as $key => $value)
 *   {
 *		 ...;
 *   }
 * into
 *		$array = expr ();
 *		foreach_reset ($arr, iter); 
 *		loop()
 *		{
 *			$T = foreach_has_key ($arr, iter);
 *			if ($T) goto L1; else goto L2;
 *		L1:
 *			$key = foreach_get_key ($arr, iter); 
 *			$val = foreach_get_val ($arr, iter); // optional
 *			....  
 *			foreach_next ($arr, iter); 
 *		}
 *		L2:
 *		foreach_end ($arr, iter);
 */

void Lower_control_flow::lower_foreach (Foreach* in, List<Statement*>* out)
{
 	// $array = expr (); (only is array is not var)
	Variable* arr; 
	if (not ((arr = dynamic_cast<Variable*> (in->expr))
		&& arr->variable_name->classid () == VARIABLE_NAME::ID
		&& arr->target == NULL
		&& arr->array_indices->size () == 0))
	{
		arr = fresh_var ("LCF_ARRAY_");
		out->push_back (new Eval_expr (new Assignment (arr, false, in->expr)));
	}

	// foreach_reset ($arr, iter); 
	HT_ITERATOR* iter = fresh_iter ();
	out->push_back (new Foreach_reset (arr->clone (), iter));

	// loop ()
	Loop* loop = new Loop (new List<Statement*>);
	Variable* has_key = fresh_var ("THK");

	// $T = foreach_has_key ($arr, iter);
	loop->statements->push_back (
		new Eval_expr (
			new Assignment (
				has_key,
				false, 
				new Foreach_has_key (
					arr->clone (),
					iter->clone ()))));

	Label* l1 = fresh_label ();
	Label* l2 = fresh_label ();

	// if ($T) goto L1; else goto L2;
	loop->statements->push_back (new Branch (has_key->clone (), l1->label_name->clone (), l2->label_name->clone ()));

	// L1:
	loop->statements->push_back (l1);




	// $key = foreach_get_key ($arr, iter); 
	
	// TODO havent taken into account a key with indices
	// The key may not be present, but we create it anyway for the unparser.
	Variable* key;
	if (in->key)
		key = in->key;
	else
		key = fresh_var ("LCF_KEY_");

	Statement* get_key = 
			new Eval_expr (
				new Assignment (
					key->clone (),
					false,
					new Foreach_get_key (
						arr->clone (),
						iter->clone ())));


	// only push it back if necessary
	if (in->key)
		loop->statements->push_back (get_key);
	

	// $val = foreach_get_val ($arr, $key, iter); 
	Foreach_get_val* get_val = new Foreach_get_val (
														arr->clone (),
														iter->clone ());

	// only add the key if it wont be found already
	if (not in->key)
		get_val->attrs->set ("phc.unparser.foreach_get_key", get_key);

	get_val->attrs->set ("phc.unparser.foreach_key", key);

	loop->statements->push_back (	new Eval_expr (
														new Assignment (
															in->val->clone (),
															in->is_ref,
															get_val)));

	// ....  
	loop->statements->push_back_all (in->statements);

	// foreach_next ($arr, iter); 
	loop->statements->push_back (
		new Foreach_next (
			arr->clone (),
			iter->clone ()));

	lower_loop(loop, out);

	// L2:
	out->push_back (l2);

	// foreach_end ($arr, iter);
	out->push_back (
		new Foreach_end (
			arr->clone (),
			iter->clone ()));

}

/* Convert 
 *   foreach ($array as $key => $value)
 *   {
 *		 ...;
 *   }
 * into
 *	  if ($array->refcount)
 *		$temp_array = $array; // copy by val
 *	  else
 *		$temp_array =& $array; // copy by ref
 *
 *	// (if array is an expression, use former form)
 *
 *	  unset ($value);
 *	  while (list ($Tkey, ) = each ($temp_array))
 *	  {
 *	   $key =& $Tkey;
 *		$value = $temp_array [$Tkey]; // use =& form for an array reference
 *		 ...
 *	  }
 *
 *	  This saves from messing about with locks, and such, which I
 *	  believe are just refcounts anyway.
 */

#if 0
void Lower_control_flow::lower_foreach (Foreach* in, List<Statement*>* out)
{
	Variable* temp_array = fresh_var ("LCF_ARRAY_");

	// we need a temporary even if the key is provided
	Variable* Tkey = fresh_var ("LCF_KEY_");

	// If the expression is a varaible then we may want to use a
	// reference. Otherwise, we just use a copy.
	// $temp_array =& $array
//	bool array_ref = (dynamic_cast<Variable*>(in->expr) != NULL);
	Eval_expr* array_copy = new Eval_expr (
		new Assignment (temp_array, in->is_ref, in->expr));

	Eval_expr* reset = NULL;
	if (in->is_ref)
	{
		// reset ($temp_array);
		reset = new Eval_expr (
				new Method_invocation (
					NULL,
					new METHOD_NAME (new String ("reset")),
					new List<Actual_parameter*> (
						new Actual_parameter (false, temp_array->clone ())
					)
				)
			);
	}

	// unset ($value);
/*	List<Actual_parameter*> *unset_params = new List<Actual_parameter*> ();
	unset_params->push_back (new Actual_parameter (false, in->val));
	Eval_expr* unset = new Eval_expr (
			new Method_invocation (NULL, 
				new METHOD_NAME (new String ("unset")),
				unset_params)
			);
*/

	// list ($Tkey, ) = each ($temp_array);
	List_assignment *assign = new List_assignment (
			new List<List_element*> (Tkey),
			new Method_invocation (
				NULL, 
				new METHOD_NAME (new String ("each")),
				new List<Actual_parameter*> (
					new Actual_parameter (false, temp_array->clone ())
				)
			)
		);

	// $key &= $Tkey;
	if (in->key)
		in->statements->push_front (
				new Eval_expr (
					new Assignment (
						in->key,
						false,
						Tkey->clone ())));


	// $value = $temp_array [$Tkey]
	// or
	// $value =& $temp_array [$Tkey]
	in->statements->push_front (
			new Eval_expr (
				new Assignment (
					in->val,
					in->is_ref,
					new Variable (
						NULL,
						temp_array->variable_name->clone (), 
						new List<Expr*> (Tkey->clone ())))
			)
		);

	// while (list ($key, ) = each ($temp_array))
   Loop* while_stmt = new Loop (assign, in->statements);

	// A continue in a for loop lands just before the increment
	add_label<Continue> (in, while_stmt->statements);

	// push it all back
	out->push_back (array_copy);
	if (reset) out->push_back (reset);
//	out->push_back (unset);
	lower_loop (while_stmt, out);
}

void Lower_control_flow::lower_foreach (Foreach* in, List<Statement*>* out)
{
	// use the same lock variable throughout the program
	static Variable* locks = fresh_var ("LCF_LOCK_");

	Variable* temp_array = fresh_var ("LCF_ARRAY_");

	// if no key is provided, use a temporary
	Variable* Tkey;
	if (in->key) Tkey = in->key;
	else Tkey = fresh_var ("LCF_KEY_");

	// If the expression is a varaible then we may want to use a
	// reference. Otherwise, we just use a copy.
	bool array_ref = (dynamic_cast<Variable*>(in->expr) != NULL);
	Eval_expr* copy  = new Eval_expr (
		new Assignment (temp_array, array_ref, in->expr));

	List <Statement*>* lock_check = new List<Statement*> ();
	Variable* lock_created;
	// if ($locks[$x]) {
	if (array_ref)
	{

		lock_created = fresh_var ("LCF_LOCK_CREATED_");

		// $tmp = $x;
		List<Statement*>* by_copy = new List<Statement*> ();
		by_copy->push_back (new Eval_expr (
					new Assignment (temp_array->clone (), true, in->expr)));
		// lock_created = false;
		by_copy->push_back (new Eval_expr (
					new Assignment (lock_created->clone (), false, new BOOL (false))));


		// else 
		// { 
		//		$tmp =& $x;
		List<Statement*>* by_ref = new List<Statement*> ();
		by_ref->push_back (new Eval_expr (
					new Assignment (temp_array->clone (), false, in->expr)));
		//		lock_created = true;
		by_ref->push_back (new Eval_expr (
					new Assignment (lock_created->clone (), false, new BOOL (false))));

		//		$locks[$x] = true; 
		// }
		by_ref->push_back (new Eval_expr (
					new Assignment (get_lock_access (in->expr), true, in->expr)));

		// Finally create the if
		lock_check->push_back (new If (get_lock_access (in->expr), by_ref, by_copy));

	}

	// reset ($temp_array);
/*	List<Actual_parameter*> *reset_params 
	= new List<Actual_parameter*> ();
	reset_params->push_back (new Actual_parameter (false, temp_array));
	Eval_expr* reset = new Eval_expr (
		new Method_invocation (NULL, 
			new METHOD_NAME (new String ("reset")),
			reset_params)
		);
*/
	// unset ($value);
/*	List<Actual_parameter*> *unset_params = new List<Actual_parameter*> ();
	unset_params->push_back (new Actual_parameter (false, in->val));
	Eval_expr* unset = new Eval_expr (
			new Method_invocation (NULL, 
				new METHOD_NAME (new String ("unset")),
				unset_params)
			);
*/

	// each ($temp_array)
	List<Actual_parameter*> *each_params 
		= new List<Actual_parameter*> ();
	each_params->push_back (new Actual_parameter (false, temp_array));
	Method_invocation *each = new Method_invocation (NULL, 
			new METHOD_NAME (new String ("each")),
			each_params);

	// list ($key, ) = each ($temp_array);
	List<List_element*> *lhss = new List< List_element*> ();
	lhss->push_back (Tkey);
	List_assignment *assign = new List_assignment (lhss, each);

	// $value = $temp_array [$Tkey]
	// or
	// $value =& $temp_array [$Tkey]
	List<Expr*> *indices = new List<Expr*> ();
	indices->push_back (Tkey);
	Variable *val = new Variable (NULL, temp_array->variable_name, indices);
	Assignment *fetch_val = new Assignment (in->val, in->is_ref, val);
	in->statements->push_front (new Eval_expr (fetch_val));

	// while (list ($key, ) = each ($temp_array))
   Loop* while_stmt = new Loop (assign, in->statements);

	// A continue in a for loop lands just before the increment
	add_label<Continue> (in, while_stmt->statements);

	// reset the lock
	Statement* lock_unset;
	if (array_ref)
	{
		//		if (lock_created);
		lock_unset = If (new Eval_expr (lock_created->clone ()));


		// unset ($lock [$asrray]);
		List<Actual_parameter*> *unset_params = new List<Actual_parameter*> ();
		unset_params->push_back (new Actual_parameter (false, get_lock_access (in->expr)));
		lock_unset->iftrue->push_back (new Eval_expr (
				new Method_invocation (NULL, 
					new METHOD_NAME (new String ("unset")),
					unset_params)
				));
	}


	// push it all back
	out->push_back (copy);
	if (array_ref) lower_if (check_lock, out);
//	if (reset) out->push_back (reset);
	lower_loop (while_stmt, out);
	if (array_ref) out->push_back (lock_unset);
}
#endif

void Lower_control_flow::post_foreach(Foreach* in, List<Statement*>* out)
{
	lower_foreach (in, out);
	// we add the continue label in lower_foreach
	add_label<Continue> (in, out);
	add_label<Break> (in, out);
	break_levels.pop_back ();
	continue_levels.pop_back ();
}


Variable* var_name_to_var (VARIABLE_NAME* var_name)
{
	return new Variable (NULL, var_name, new List<Expr*>);
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
void Lower_control_flow::lower_exit (T* in, List<Statement*>* out)
{
	vector<Node*> *levels;
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
		out->push_back (new Goto ((exit_label<T> (level))->label_name->clone ()));
	}
	else
	{
		// Otherwise we create a label and a goto for each possible loop, and attach
		// the label to the goto.
		//
		// $TB1 = $x;
		VARIABLE_NAME* lhs = fresh_var_name ("TB");
		out->push_back (
			new Eval_expr (
				new Assignment (
					var_name_to_var (lhs), // TODO: remove var_name_to_var when changing IR definition
					false, 
					in->expr)));

		// 1 branch and label per level:
		//		if ($TB1 = 1) goto L1; else goto L2;
		//	L2:
		vector<Node*>::reverse_iterator i;
		int depth;
		for (i = levels->rbegin (), depth = 1; i != levels->rend (); i++, depth++)
		{
			// We break to depth 1 for any expr <= 1
			OP* op = new OP (new String ("=="));
			if (depth == 1)
				op = new OP (new String ("<="));

			//	if ($TB1 == depth) goto L1; else goto L2;
			Label* iffalse = fresh_label ();
			push_back_pieces ( // push the pieces from the eval_var back
				new Branch (
					var_name_to_var (eval_var (new Bin_op ( // TODO remove var_name_to_var when changing IR definition
						lhs->clone(),
						op,
						eval_var (new INT (depth))))),
					exit_label<T> (*i)->label_name, // get the label from this depth
					iffalse->label_name->clone ()),
				out);

			//	L2:
			out->push_back (iffalse);
		}
		assert (depth == num_levels + 1);

		// Print an error, and die with 255
		stringstream ss;
		ss <<	"<?php echo (\"\nFatal error: Cannot break/continue $"
			<< (*lhs->value)
			<< " levels in " << *(in->get_filename ())
			<< " on line " << in->get_line_number () << "\n\");\n"
			<< "die (255);?>";

		out->push_back_all (parse_to_hir (new String (ss.str()), in));
	}
}

void Lower_control_flow::post_break (Break* in, List<Statement*>* out)
{
	lower_exit<Break> (in, out);
}

void Lower_control_flow::post_continue (Continue* in, List<Statement*>* out)
{
	lower_exit<Continue> (in, out);
}


void Lower_control_flow::pre_control_flow (Statement* in, List<Statement*>* out)
{
	break_levels.push_back (in);
	continue_levels.push_back (in);
	out->push_back (in);
}


void Lower_control_flow::pre_loop(Loop* in, List<Statement*>* out)
{
	pre_control_flow (in, out);
}

void Lower_control_flow::pre_foreach(Foreach* in, List<Statement*>* out)
{
	pre_control_flow (in, out);
}
