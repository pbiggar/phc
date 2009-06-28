/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * shredder (n.): a machine that tears objects into smaller pieces.
 * Transform the AST into 3AC-like code.
 */

#include "AST_annotate.h"
#include "AST_shredder.h"
#include "process_ir/General.h"

using namespace AST;

void Shredder::children_php_script(PHP_script* in)
{
	Annotate ann;
	in->visit(&ann);

	Lower_expr::children_php_script(in);
}

/*
 * Variables (array indexing, object indexing)
 *
 * We do the indexing bit-by-bit. For example, for $c->a[1][2][3], we get
 *
 *	$T0 =& $c->arr;
 *	$T1 =& $T0[1];
 *	$T2 =& $T1[2];
 *	$T2[3] ... ;
 *
 * However, we always stop one short, as in $T2 above. This is necessary in the
 * case of unset, returning by reference, and a number of other cases.
 *
 * Note that it is important to use reference assignment, because when we
 * assign to $T2[2] above, we want the original object $c to be modified.
 *
 * However, introducing references where there were no references before will
 * result in an element being inserted in the array if the element is
 * missing, or the array is NULL. For example,
 *
 *		$x = $y[5];
 *
 *	is different than
 *
 *		$x =& $y[5];
 *
 *	since $y has no index 5.
 *
 * As a result, we use reference assignment only if there is an implicit
 * reference, or reference assignment is used.
 */

Variable* Shredder::post_variable(Variable* in)
{
	if (in->attrs->is_true ("phc.ast_shredder.dont_shred"))
		return in;

	Variable* prev = in;
	
	int num_pieces = 
		  (in->target != NULL ? 1 : 0) 
		+ in->array_indices->size()
		- (in->attrs->is_true("phc.ast_shredder.need_addr") ? 1 : 0);

	// translate ${$x}[1] to $T =& ${$x}; $T[1] but only if no target is set
	if(in->target == NULL 
		&& in->variable_name->classid() == Reflection::ID
		&& !in->attrs->is_true ("phc.ast_lower_expr.no_temp"))
	{
		Variable* temp = fresh_var("TSr");

		pieces->push_back(
			new Eval_expr(
				new Assignment(
					temp->clone (), 
					in->attrs->is_true ("phc.ast_shredder.use_ref"),
					new Variable (in->variable_name))));

		prev = temp;
	}

	if(in->target != NULL && num_pieces > 0)
	{
		Variable* temp = fresh_var("TSt");
		pieces->push_back(new Eval_expr(new Assignment(
			temp->clone (),
			in->attrs->is_true ("phc.ast_shredder.use_ref"),
			new Variable (
				in->target,
				in->variable_name->clone(),
				new Expr_list
			))));
		prev = temp;
		num_pieces--;

		// TODO: this destructively modifies *in. is that what we want?
		in->target = NULL;
	}

	while(num_pieces > 0)
	{
		// Get the array index (can be NULL)
		Expr* array_index = in->array_indices->front ();
		if (array_index)
			array_index = array_index->clone ();
		// TODO: this destructively modifies *in. is that what we want?
		in->array_indices->pop_front();


		Variable* temp = fresh_var("TSi");
		pieces->push_back(new Eval_expr(new Assignment(
			temp->clone (),
			in->attrs->is_true ("phc.ast_shredder.use_ref"),
			new Variable (
				NULL, 
				prev->variable_name->clone(), 
				new Expr_list (array_index)))));
		prev = temp;
		num_pieces--;
	}

	if(prev != in && !in->array_indices->empty())
	{
		prev = prev->clone();
		Expr* front = in->array_indices->front();
		in->array_indices->pop_front();

		if (front) // NULL expressions are allowed
			front = front->clone ();

		prev->array_indices->push_back(front);
	}

	return prev;
}

/*
 * Binary and unary operators
 *
 * The "lazy" binary operators (&&, ||, and friends) are not dealt with here, 
 * but in the lowering pass. Pre and post operators are handled in Early_Shredder.
 */

Expr* Shredder::post_bin_op(Bin_op* in)
{
	return eval(in);
}

Expr* Shredder::post_unary_op(Unary_op* in)
{
	return eval(in);
}

/*
 * Casts
 */

Expr* Shredder::post_cast(Cast* in)
{
	return eval(in);
}

/*
 * instanceof
 */

Expr* Shredder::post_instanceof (Instanceof* in)
{
	return eval(in);
}

/*
 * Method invocation
 */

Expr* Shredder::post_method_invocation(Method_invocation* in)
{
	return eval(in);
}

Expr* Shredder::post_new (New* in)
{
	return eval(in);
}

/*
 * Literals
 */

/* In most cases, it isnt required to shred literals, but it simplifies matters
 * a great deal. If we don't shred these, then we need to simplify reflections
 * and branches with immediate values, run a constant-folding pass after
 * switch-lowering, remove literals in statements by themselves, and allow the
 * unparser to print unprintable variables (like $5 or ${""}). All of these
 * changes would then have to be duplicated in the MIR. It is simpler to shred
 * here, and just make the changes in the MIR. */

Expr* Shredder::post_int(INT* in)
{
	return eval(in);
}

Expr* Shredder::post_real(REAL* in)
{
	return eval(in);
}

Expr* Shredder::post_string(STRING* in)
{
	return eval(in);
}

Expr* Shredder::post_bool(BOOL* in)
{
	return eval(in);
}

Expr* Shredder::post_nil(NIL* in)
{
	return eval(in);
}

Expr* Shredder::post_constant (Constant* in)
{
	return eval(in);
}

/*
 * Translate into canonical tree form (replace assignments within expressions
 * with an assignment and a variable access:
 *
 * Translate
 *
 *	  $x = $y = 5;
 *
 *	into
 *
 *	  $y = 5;
 *	  $t1 = $y;
 *	  $x = $t1;
 */
Expr* Shredder::post_assignment (Assignment* in)
{
	if (in->attrs->is_true ("phc.ast_shredder.non_nested_assignment"))
		return in;

	// dont replace with the same variable, since it may be assigned to multiple
	// times in the same expression.
	pieces->push_back (new Eval_expr (in));
	return eval (in->variable);
}

/*
 * Array literals
 */

Expr* Shredder::post_array(Array* in)
{
	if (in->attrs->is_true("phc.ast_lower_expr.no_temp"))
		return in;

	Variable* var = fresh_var ("TSa");

	// We need to unset TS in case its run in a loop
	pieces->push_back(new Eval_expr(new Method_invocation("unset", var->clone ())));

	// We need to cast it in case its empty
	pieces->push_back(
		new Eval_expr (
			new Assignment (
				var->clone (), 
				false, 
				new Cast(
					"array", 
					new String ("array"), 
					var->clone ()))));


	// It makes it much much easier to analyse if we don't throw this
	// information away. A key without an index uses the next largest key. 
	int key_count = 0;
	bool use_count = true;
	foreach (Array_elem* ae, *in->array_elems)
	{
		Expr* key;

		if(ae->key != NULL)
		{
			key = ae->key;

			// This disrupts the count (we could carry on, but it'll only helpful
			// in rare occasions).
			use_count = false;
		}
		else if (use_count)
		{
			key = new INT (key_count);
			key_count++;
		}
		else
			key = NULL;

		pieces->push_back(
			new Eval_expr(
				new Assignment(
					new Variable (
						NULL,
						var->variable_name->clone(),
						new Expr_list (key)),
					ae->is_ref,
					ae->val)));
	}

	return new Variable (var->variable_name->clone ());
}

/* Turn
 *
 *		$x[...] += $y;
 *
 *	into
 *
 *		$T &= $x[...]
 *		$T = $T + $y;
 *
 *	If $x is a simple variable, simply turn into
 *
 *		$x = $x + $y;
 */
Expr* Shredder::post_op_assignment(Op_assignment* in)
{
	Assignment* assignment;

	// The LHS may be of the form $x[$y], but that should occur
	// as an operand to a binary operator. Hence, we must visit the RHS again
	// clearing the need_addr flag
	in->variable->attrs->erase("phc.ast_shredder.need_addr");

	Variable* lhs = in->variable;
	// If not a simple varaible, then $lhs &= $x[...];
	if (!lhs->is_simple_variable ())
	{
		lhs = fresh_var ("Toa");
		Expr* copy = new Assignment (
				lhs->clone (),
				true,
				in->variable);

		copy->transform_children (this);
		pieces->push_back (new Eval_expr (copy));
	}

	// Create $T = $T + $y;
	assignment = new Assignment(
		lhs,
		false,
		new Bin_op (
			lhs->clone (),
			in->op, 
			in->expr));

	assignment->attrs = in->attrs;

	// This might still be nested assignment
	return post_assignment (assignment);
}

Expr* Shredder::pre_ignore_errors(Ignore_errors* in)
{
	Variable* zero = fresh_var("TSie");
	Variable* temp = fresh_var("TSie");
	pieces->push_back(new Eval_expr(new Assignment(
		zero,
		false,
		new INT(0))));
	pieces->push_back(new Eval_expr(new Assignment(
		temp,
		false,
		new Method_invocation(
			"error_reporting",
			zero->clone ()))));
	in->attrs->set("phc.ast_shredder.old_error_level", temp->clone ());
	return in;
}

Expr* Shredder::post_ignore_errors(Ignore_errors* in)
{
	Variable* temp = fresh_var("TSie");
	Variable* old = dynamic_cast<Variable*>(in->attrs->get("phc.ast_shredder.old_error_level"));
	in->attrs->erase ("phc.ast_shredder.old_error_level");
	assert(old);
	
	(*pieces
		<< temp << " = error_reporting (" << old << ");"
	).finish (in);

	return in->expr;
}
