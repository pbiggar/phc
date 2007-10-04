/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * shredder (n.): a machine that tears objects into smaller pieces.
 * Transform the AST into 3AC-like code.
 */

#include "Shredder.h"
#include "fresh.h"

// For development only
#include "process_ast/XML_unparser.h"
#include "process_ast/PHP_unparser.h"
#include "process_ast/Consistency_check.h"


/*
 * Remove unparser attributes and desugar
 */

/* Shred a list of statements */
List<AST_statement*>* shred (List<AST_statement*>* in)
{
	AST_php_script* script = new AST_php_script (in);
	script->transform_children (new Shredder ());
	return script->statements;
}

List<AST_statement*>* shred (AST_statement* in)
{
	AST_php_script* script = new AST_php_script (new List<AST_statement*> (in));
	script->transform_children (new Shredder ());
	return script->statements;
}

void Shredder::children_php_script(AST_php_script* in)
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

AST_variable* Shredder::post_variable(AST_variable* in)
{
	if (in->attrs->is_true ("phc.shredder.dont_shred"))
		return in;

	AST_variable* prev = in;
	
	int num_pieces = 
		  (in->target != NULL ? 1 : 0) 
		+ in->array_indices->size()
		- (in->attrs->is_true("phc.shredder.need_addr") ? 1 : 0);

	// translate ${$x}[1] to $T =& ${$x}; $T[1] but only if no target is set
	if(in->target == NULL 
		&& in->variable_name->classid() == AST_reflection::ID
		&& !in->attrs->is_true ("phc.lower_expr.no_temp"))
	{
		AST_variable* temp = fresh_var("TSr");

		pieces->push_back(new AST_eval_expr(new AST_assignment(
			temp->clone (), 
			in->attrs->is_true ("phc.shredder.need_addr"),
			new AST_variable (
				NULL,
				in->variable_name,
				new List<AST_expr*>()
			))));

		prev = temp;
	}

	if(in->target != NULL && num_pieces > 0)
	{
		AST_variable* temp = fresh_var("TSt");
		pieces->push_back(new AST_eval_expr(new AST_assignment(
			temp->clone (),
			in->attrs->is_true ("phc.shredder.need_addr"),
			new AST_variable (
				in->target,
				in->variable_name->clone(),
				new List<AST_expr*>()
			))));
		prev = temp;
		num_pieces--;

		// TODO: this destructively modifies *in. is that what we want?
		in->target = NULL;
	}

	while(num_pieces > 0)
	{
		AST_variable* temp = fresh_var("TSi");
		pieces->push_back(new AST_eval_expr(new AST_assignment(
			temp->clone (),
			in->attrs->is_true ("phc.shredder.need_addr"),
			new AST_variable (
				NULL, 
				prev->variable_name->clone(), 
				new List<AST_expr*>(in->array_indices->front()->clone ())))));
		prev = temp;
		num_pieces--;

		// TODO: this destructively modifies *in. is that what we want?
		in->array_indices->pop_front();
	}

	if(prev != in && !in->array_indices->empty())
	{
		prev = prev->clone();
		AST_expr* front = in->array_indices->front();
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
void Shredder::pre_eval_expr (AST_eval_expr* in, List<AST_statement*>* out)
{
	if (in->expr->classid () != AST_variable::ID)
		out->push_back (in);
}

/*
 * Binary and unary operators
 *
 * The "lazy" binary operators (&&, ||, and friends) are not dealt with here, 
 * but in the lowering pass. Pre and post operators are handled in Early_Shredder.
 */

AST_expr* Shredder::post_bin_op(AST_bin_op* in)
{
	return eval(in);
}

AST_expr* Shredder::post_unary_op(AST_unary_op* in)
{
	return eval(in);
}

/*
 * Casts
 */

AST_expr* Shredder::post_cast(AST_cast* in)
{
	return eval(in);
}

/*
 * Method invocation
 */

AST_expr* Shredder::post_method_invocation(AST_method_invocation* in)
{
	return eval(in);
}

/*
 * Literals
 */

AST_expr* Shredder::post_int(Token_int* in)
{
	return eval(in);
}

AST_expr* Shredder::post_real(Token_real* in)
{
	return eval(in);
}

AST_expr* Shredder::post_string(Token_string* in)
{
	return eval(in);
}

AST_expr* Shredder::post_bool(Token_bool* in)
{
	return eval(in);
}

AST_expr* Shredder::post_null(Token_null* in)
{
	return eval(in);
}

AST_expr* Shredder::post_constant (AST_constant* in)
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
AST_expr* Shredder::post_assignment (AST_assignment* in)
{
	if (in->attrs->is_true ("phc.shredder.non_nested_assignment"))
		return in;

	// dont replace with the same variable, since it may be assigned to multiple
	// times in the same expression.
	pieces->push_back (new AST_eval_expr (in));
	return eval (in->variable);
}

/*
 * Array literals
 */

AST_expr* Shredder::post_array(AST_array* in)
{
	if (in->attrs->is_true("phc.lower_expr.no_temp"))
		return in;

	AST_variable* var = fresh_var ("TSa");

	// We need to unset TS in case its run in a loop
	pieces->push_back(new AST_eval_expr(new AST_method_invocation("unset", var->clone ())));

	// We need to cast it in case its empty
	pieces->push_back(
		new AST_eval_expr (new AST_assignment (var->clone (), false, new AST_cast("array", var->clone ()))));
	

	List<AST_array_elem*>::const_iterator i;
	for(i = in->array_elems->begin(); i != in->array_elems->end(); i++)
	{
		AST_expr* key;

		if((*i)->key != NULL)
			key = (*i)->key;
		else
			key = NULL;

		pieces->push_back(new AST_eval_expr(new AST_assignment(
						new AST_variable (
							NULL,
							var->variable_name->clone(),
							new List<AST_expr*>(key)),
						(*i)->is_ref,
						(*i)->val
						)));
	}

	return new AST_variable (
			NULL,
			var->variable_name->clone (),
			new List<AST_expr*>());
}

AST_expr* Shredder::post_op_assignment(AST_op_assignment* in)
{
	AST_assignment* assignment;

	// The LHS may be of the form $x[$y], but that should occur
	// as an operand to a binary operator. Hence, we must visit the RHS again
	// clearing the need_addr flag
	AST_expr* left = in->variable->clone();
	left->attrs->erase("phc.shredder.need_addr");
	left = transform_expr(left);

	assignment = new AST_assignment(
		in->variable,
		false,
		new AST_bin_op(
			left,
			in->op,
			in->expr)
		);
	assignment->attrs = in->attrs;
	
	return post_assignment(assignment); 
}

AST_expr* Shredder::pre_ignore_errors(AST_ignore_errors* in)
{
	AST_variable* zero = fresh_var("TSie");
	AST_variable* temp = fresh_var("TSie");
	pieces->push_back(new AST_eval_expr(new AST_assignment(
		zero,
		false,
		new Token_int(0))));
	pieces->push_back(new AST_eval_expr(new AST_assignment(
		temp,
		false,
		new AST_method_invocation(
			"error_reporting",
			zero))));
	in->attrs->set("phc.shredder.old_error_level", temp);
	return in;
}

AST_expr* Shredder::post_ignore_errors(AST_ignore_errors* in)
{
	AST_variable* temp = fresh_var("TSie");
	AST_variable* old = dynamic_cast<AST_variable*>(in->attrs->get("phc.shredder.old_error_level"));
	assert(old);
	
	pieces->push_back(new AST_eval_expr(new AST_assignment(
		temp,
		false,
		new AST_method_invocation(
			"error_reporting",
			old))));
	
	return in->expr;
}

/*
 * Convert
 *		unset($x, $y, $z);
 * into
 *		unset($x);
 *		unset($y);
 * 		unset($z);
 */
void Split_unset_isset::pre_eval_expr(AST_eval_expr * in, List<AST_statement*>* out)
{
	AST_expr* unset = new AST_method_invocation(
		NULL, 	// NULL target
		new Token_method_name(new String("unset")),
		NULL	// Arbitrary list of parameters
		);

	if(in->expr->match(unset))
	{
		AST_method_invocation* inv = dynamic_cast<AST_method_invocation*>(in->expr);
		assert(inv);

		List<AST_actual_parameter*>::const_iterator i;
		for(i = inv->actual_parameters->begin();
			i != inv->actual_parameters->end();
			i++)
		{
			assert(!(*i)->is_ref);
			out->push_back(new AST_eval_expr(new AST_method_invocation("unset", (*i)->expr)));
		}
	}
	else
	{
		out->push_back(in);
	}
}

/*
 * convert
 * 		isset($x, $y, $z)
 * into
 * 		isset($x) && isset($y) && isset($z)
 */
AST_expr* Split_unset_isset::pre_method_invocation(AST_method_invocation* in)
{
	if(in->method_name->match(new Token_method_name(new String("isset"))))
	{
		List<AST_expr*>* terms = new List<AST_expr*>;

		List<AST_actual_parameter*>::const_iterator i;
		for(i = in->actual_parameters->begin();
			i != in->actual_parameters->end();
			i++)
		{
			assert(!(*i)->is_ref);
			terms->push_back(new AST_method_invocation("isset", (*i)->expr));
		}

		List<AST_expr*>::const_iterator j = terms->begin();
		AST_expr* result = *j++;
		for( ; j != terms->end(); j++)
		{
			result = new AST_bin_op(result, *j, "&&");	
		}

		return result;
	}
	else
	{
		return in;
	}
}

AST_expr* Translate_empty::pre_method_invocation(AST_method_invocation* in)
{
	if(in->method_name->match(new Token_method_name(new String("empty"))))
	{
		Token_cast* boolean = new Token_cast(new String("boolean"));
		AST_actual_parameter* param = *in->actual_parameters->begin();
		assert(!param->is_ref);
		return new AST_unary_op(new AST_cast(boolean, param->expr), "!");
	}
	else
	{
		return in;
	}
}
