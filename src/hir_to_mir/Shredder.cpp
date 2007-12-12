/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * shredder (n.): a machine that tears objects into smaller pieces.
 * Transform the HIR into 3AC-like code.
 */

#include "Annotate.h"
#include "Shredder.h"
#include "process_ir/fresh.h"
#include "process_ir/General.h"

using namespace HIR;

/* Shred a list of statements */
List<Statement*>* shred (List<Statement*>* in)
{
	PHP_script* script = new PHP_script (in);
	script->transform_children (new Shredder ());
	return script->statements;
}

List<Statement*>* shred (Statement* in)
{
	PHP_script* script = new PHP_script (new List<Statement*> (in));
	script->transform_children (new Shredder ());
	return script->statements;
}

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
	if (in->attrs->is_true ("phc.shredder.dont_shred"))
		return in;

	Variable* prev = in;
	
	int num_pieces = 
		  (in->target != NULL ? 1 : 0) 
		+ in->array_indices->size()
		- (in->attrs->is_true("phc.shredder.need_addr") ? 1 : 0);

	// translate ${$x}[1] to $T =& ${$x}; $T[1] but only if no target is set
	if(in->target == NULL 
		&& in->variable_name->classid() == Reflection::ID
		&& !in->attrs->is_true ("phc.lower_expr.no_temp"))
	{
		Variable* temp = fresh_var("TSr");

		pieces->push_back(new Eval_expr(new Assignment(
			temp->clone (), 
			in->attrs->is_true ("phc.shredder.need_addr"),
			new Variable (
				NULL,
				in->variable_name,
				new List<Expr*>()
			))));

		prev = temp;
	}

	if(in->target != NULL && num_pieces > 0)
	{
		Variable* temp = fresh_var("TSt");
		pieces->push_back(new Eval_expr(new Assignment(
			temp->clone (),
			in->attrs->is_true ("phc.shredder.need_addr"),
			new Variable (
				in->target,
				in->variable_name->clone(),
				new List<Expr*>()
			))));
		prev = temp;
		num_pieces--;

		// TODO: this destructively modifies *in. is that what we want?
		in->target = NULL;
	}

	while(num_pieces > 0)
	{
		Variable* temp = fresh_var("TSi");
		pieces->push_back(new Eval_expr(new Assignment(
			temp->clone (),
			in->attrs->is_true ("phc.shredder.need_addr"),
			new Variable (
				NULL, 
				prev->variable_name->clone(), 
				new List<Expr*>(in->array_indices->front()->clone ())))));
		prev = temp;
		num_pieces--;

		// TODO: this destructively modifies *in. is that what we want?
		in->array_indices->pop_front();
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

/* Remove statements which consist of a single variable. These can be
 * introduced by the list lowering. We use the pre_ form, since the post_ form
 * overrides Lower_expr::post_eval_expr.*/
void Shredder::pre_eval_expr (Eval_expr* in, List<Statement*>* out)
{
	if (in->expr->classid () != Variable::ID)
		out->push_back (in);
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
 * foreach
 */

Expr* Shredder::post_foreach_has_key (Foreach_has_key* in)
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
	if (in->attrs->is_true ("phc.shredder.non_nested_assignment"))
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
	if (in->attrs->is_true("phc.lower_expr.no_temp"))
		return in;

	Variable* var = fresh_var ("TSa");

	// We need to unset TS in case its run in a loop
	pieces->push_back(new Eval_expr(new Method_invocation("unset", var->clone ())));

	// We need to cast it in case its empty
	pieces->push_back(
		new Eval_expr (new Assignment (
									var->clone (), 
									false, 
									new Cast(
										"array", 
										new String ("array"), 
										var->clone ()))));
	

	List<Array_elem*>::const_iterator i;
	for(i = in->array_elems->begin(); i != in->array_elems->end(); i++)
	{
		Expr* key;

		if((*i)->key != NULL)
			key = (*i)->key;
		else
			key = NULL;

		pieces->push_back(new Eval_expr(new Assignment(
						new Variable (
							NULL,
							var->variable_name->clone(),
							new List<Expr*>(key)),
						(*i)->is_ref,
						(*i)->val
						)));
	}

	return new Variable (
			NULL,
			var->variable_name->clone (),
			new List<Expr*>());
}

Expr* Shredder::post_op_assignment(Op_assignment* in)
{
	Assignment* assignment;

	// The LHS may be of the form $x[$y], but that should occur
	// as an operand to a binary operator. Hence, we must visit the RHS again
	// clearing the need_addr flag
	Expr* left = in->variable->clone();
	left->attrs->erase("phc.shredder.need_addr");
	left = transform_expr(left);

	assignment = new Assignment(
		in->variable,
		false,
		new Bin_op(
			left,
			in->op,
			in->expr)
		);
	assignment->attrs = in->attrs;
	
	return post_assignment(assignment); 
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
			zero))));
	in->attrs->set("phc.shredder.old_error_level", temp);
	return in;
}

Expr* Shredder::post_ignore_errors(Ignore_errors* in)
{
	Variable* temp = fresh_var("TSie");
	Variable* old = dynamic_cast<Variable*>(in->attrs->get("phc.shredder.old_error_level"));
	assert(old);
	
	pieces->push_back(new Eval_expr(new Assignment(
		temp,
		false,
		new Method_invocation(
			"error_reporting",
			old))));
	
	return in->expr;
}
