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
#include "Check_lowering.h"
#include "process_ir/fresh.h"
#include "process_ir/General.h"
#include <sstream>
#include "Shredder.h"

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
 *		do { y (); } 
 *		while ($x)
 * into
 *		L1:
 *			y ();
 *			if ($x) goto L1:
 *			else goto L2:
 *		L2:
 */
void Lower_control_flow::lower_do (Do* in, List<Statement*>* out)
{
	Label* l1 = fresh_label ();
	Label* l2 = fresh_label ();

	// make the if
	Branch* branch = new Branch (in->expr, l1->label_name->clone (), l2->label_name->clone ());

	// generate the code
	out->push_back (l1);
	out->push_back_all (in->statements);
	out->push_back (branch);
	out->push_back (l2);
}

void Lower_control_flow::post_do (Do* in, List<Statement*>* out)
{
	add_label<Continue> (in, out);
	lower_do (in, out);
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
 *		L2:
 *		}
 *		foreach_end ($arr, iter);
 */

// TODO move shredder earlier. this is made a lot more complicated by non-shredded expressions
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

	// L2:
	loop->statements->push_back (l2);

	lower_loop (loop, out);


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
 *		if (val == expr1) goto L1; else goto N1;
 *	N1:
 *		if (val == expr2) goto L2; else goto N2;
 *	N2:
 *		if (val == expr3) goto L3; else goto N3;
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
void Lower_control_flow::lower_switch(Switch* in, List<Statement*>* out)
{
	// val = expr;
	Variable *lhs = fresh_var ("TL");
	Assignment* assign = new Assignment (lhs, false, in->expr);
	out->push_back (new Eval_expr (assign));

	List<Statement*> *branches = new List<Statement*> ();
	List<Statement*> *blocks = new List<Statement*> ();

	List<Switch_case*> *cases = in->switch_cases;
	List<Switch_case*>::const_iterator i;

	// we need to know the header of the next block ahead of time
	Label* next_block_header = fresh_label ();
	Goto* _default = NULL;
	for (i = cases->begin (); i != cases->end (); i++)
	{
		Label* header = next_block_header;
		next_block_header = fresh_label ();

		if ((*i)->expr == NULL) // default
		{
			assert (_default == NULL);
			_default = new Goto (header->label_name->clone ());
		}
		else
		{
			// the else branch just goes to the next line. We dont allow NULL else
			// statements (perhaps we should?).
			Label* next = fresh_label ();

			// make the comparison
			Branch* branch = new Branch (
					new Bin_op (
						lhs->clone (), 
						new OP (new String ("==")),
						(*i)->expr
					),
					header->label_name->clone (),
					next->label_name->clone ()
				);

			branches->push_back (branch);
			branches->push_back (next);
		}

		blocks->push_back (header);
		blocks->push_back_all ((*i)->statements);
		blocks->push_back (new Goto (next_block_header->label_name->clone ())); // fallthrough
	}
	blocks->push_back (next_block_header);

	if (_default) 
		branches->push_back (_default);
	else // if default is blank jump to the end
		branches->push_back (new Goto (next_block_header->label_name->clone ()));

	out->push_back_all (branches);
	out->push_back_all (blocks);
}

void Lower_control_flow::post_switch(Switch* in, List<Statement*>* out)
{
	lower_switch (in, out);
	// A continue is the same as a break, so add the label at the same place
	add_label<Continue> (in, out);
	add_label<Break> (in, out);
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
template <class T>
void Lower_control_flow::lower_exit (T* in, List<Statement*>* out)
{
	List<Node*> *levels; // It gets uglier
	if (Break::ID == in->ID) levels = &break_levels;
	if (Continue::ID == in->ID) levels = &continue_levels;
	assert (levels);

	// check that we arent being asked to jump further than we know we can go
	unsigned int error_depth = 0;
	INT *_int = dynamic_cast<INT*> (in->expr);

	/* If this break has a NULL expression, it's much easier (and gives more
	 * readable output) if we special case it. Also, break 1 is the same as
	 * break < 1, which is the same as just break. Its easier to handle it all
	 * together. */
	// TODO what about 'break "my_string"?'
	if (in->expr == NULL || (_int && _int->value <= 1))
		error_depth = 1;
	else if (_int)
		error_depth = _int->value;

	if (error_depth > levels->size ())
	{
		// find a good node to put the error on
		Node* error_node = in->expr;
		if (error_node == NULL)
			error_node = in;
		phc_error ("Cannot break/continue %d levels", error_node, error_depth);
	}

	// Since we compare to the expression, we need to create a variable for it.
	Variable *lhs = fresh_var ("TB");

	if (in->expr)
		out->push_back (new Eval_expr (
					new Assignment (lhs, false, in->expr)));
	else
		out->push_back (new Eval_expr (
					new Assignment (lhs, false, new INT (1))));

	if (levels->size ())
	{
		INT *_int = dynamic_cast<INT*> (in->expr);
		if (in->expr == NULL || (_int && _int->value <= 1))
		{
			// Create a label, pushback a goto to it, and attach it as an attribute
			// of the innermost looping construct.
			Node* level = levels->back ();
			out->push_back (new Goto ((exit_label<T> (level))->label_name->clone ()));
		}
		else
		{
			// Otherwise we create a label and a goto for each possible loop, and attach
			// the label it the loop.

			// 1 branch and label per level:
			//		if ($TB1 = 1) goto L1; else goto L2;
			//	L2:
			List<Node*>::reverse_iterator i;
			unsigned int depth = 1;
			for (i = levels->rbegin (); i != levels->rend (); i++)
			{
				// FYI: Objects/strings evaluate to 0
				Node* level = (*i);

				// Attach the break target to the loop construct.
				Label* iftrue = exit_label<T> (level)->clone ();

				// Create: if ($TB1 == depth)
				OP* op = new OP (new String ("=="));
				INT* branch_num = new INT (depth);
				Bin_op* compare = new Bin_op (lhs->clone (), op, branch_num);

				// We break to depth 1 for any expr <= 1
				if (depth == 1)
					compare->op = new OP (new String ("<="));

				Label* iffalse = fresh_label ();
				Branch* branch = new Branch (compare, iftrue->label_name->clone (), iffalse->label_name->clone ());

				out->push_back (branch);
				out->push_back (iffalse);
				depth ++;
			}
			assert (depth == break_levels.size () + 1);
		}
	}

	// Print an error, and die with 255
	stringstream ss;
	ss <<	"<?php echo (\"\nFatal error: Cannot break/continue \\$"
		<< *(dynamic_cast<VARIABLE_NAME*> (lhs->variable_name)->value)
		<< " levels in " << *(in->get_filename ())
		<< " on line " << in->get_line_number () << " \n\");\n"
		<< "die (255);?>";

	out->push_back_all (parse_to_hir (new String (ss.str()), in));
 
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

void Lower_control_flow::pre_do(Do* in, List<Statement*>* out)
{
	pre_control_flow (in, out);
}

void Lower_control_flow::pre_foreach(Foreach* in, List<Statement*>* out)
{
	pre_control_flow (in, out);
}

void Lower_control_flow::pre_switch(Switch* in, List<Statement*>* out)
{
	pre_control_flow (in, out);
}
