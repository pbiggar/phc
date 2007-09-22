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


// Split echos into multiple statements. Normal function calls evaluate all
// their actual parameters at once, and then call the expression with the
// results of the evaluations. Echo, however, only evaluates its next argument
// after printing the result of the previouis argument. Functions with
// side-effects will display this.
//
// Convert
//	  echo f (), f();
//	into
//	  print f();
//	  print f();
//
//	We convert to print simply so the later print transformation is easier.
class Echo_split : public AST_transform
{
	void pre_eval_expr(AST_eval_expr* in, List<AST_statement*>* out)
	{
		AST_method_invocation* echo = new AST_method_invocation (
				NULL,	
				new Token_method_name (new String("echo")),
				NULL); // match any list (note this doesnt get populated. Use in STMT get the list.)

		if (not in->expr->match (echo))
		{
			out->push_back (in);
			return;
		};

		List<AST_actual_parameter*>* params =
			(dynamic_cast <AST_method_invocation*> (in->expr))->actual_parameters;
		assert (params);

		List<AST_actual_parameter*>::const_iterator i;
		for (i = params->begin (); i != params->end(); i++)
		{
			out->push_back (new AST_eval_expr (
							new AST_method_invocation (
								NULL,
								new Token_method_name (new String ("print")),
								new List<AST_actual_parameter*> (*i))));

		}
	}

};


class Desugar : public AST_transform
{
public:
	//   $x[f()] += 1;
	// 
	// is represented as 
	// 
	//   $x[f()] = $x[f()] + 1; // phc.unparser.opeq is set
	//
	// Since f() would be executed twice, it would be incorrect for any
	// side-effecting expression. We convert to
	//
	//	  $tmp = f();
	//   $x[$tmp] = $x[$tmp] + 1;
	
	void post_eval_expr(AST_eval_expr* in, List<AST_statement*>* out)
	{
		AST_assignment* assignment = dynamic_cast <AST_assignment*> (in->expr);
		if (assignment == NULL 
			or !assignment->attrs->is_true ("phc.unparser.is_opeq"))
		{
			out->push_back (in);
			return;
		}


		// the variables and expressions are identical
		AST_variable* lhs = assignment->variable;
		AST_variable* rhs = dynamic_cast <AST_variable*> (
			(dynamic_cast<AST_bin_op*>(assignment->expr))->left);
		assert (lhs->equals (rhs));

		// generate a temp for each non-literal expression.

		List<AST_expr*>::iterator i;
		List<AST_expr*>::iterator j;
		for (i = lhs->array_indices->begin(), j = rhs->array_indices->begin();
				i != lhs->array_indices->end(), j != rhs->array_indices->end();
				i++, j++)
		{
			if (dynamic_cast<AST_literal*>(*i))
				continue;

			AST_variable* tmp = fresh_var ("Topeq");
			out->push_back (new AST_eval_expr (new AST_assignment (tmp, false, (*i))));
			(*i) = tmp->clone ();
			(*j) = tmp->clone ();
		}

		out->push_back (in);
	}

	// All eval_expr must be assignments; if they are not, we generate
	// a dummy assignment on the LHS
	void pre_eval_expr(AST_eval_expr* in, List<AST_statement*>* out)
	{
		if(in->expr->classid() != AST_assignment::ID)
		{
			in->expr = new AST_assignment(fresh_var("TSe"), false, in->expr);
		}
	
		out->push_back(in);
	}

	// NOP statements are removed
	void pre_nop(AST_nop* in, List<AST_statement*>* out)
	{
		// Leave "out" empty 
	}

	// Replace "-x" by "0 - x"
	AST_expr* pre_unary_op(AST_unary_op* in)
	{
		if(*in->op->value == "-") return new AST_bin_op(
			new Token_int(0),
			in->op,
			in->expr);
		else
			return in;
	}

	// All return statements must get an argument (NULL if none specified)
	void pre_return(AST_return* in, List<AST_statement*>* out)
	{
		if(in->expr == NULL)
		{
			in->expr = new Token_null(new String("NULL"));
		}

		out->push_back(in);
	}
};

class Annotate : public AST_visitor
{
	// only generate array elements if this is set
	bool generate_array_temps;
	bool return_by_ref;

public:

	Annotate() : generate_array_temps(true) {}

	void pre_node(AST_node* in)
	{
		in->attrs->erase("phc.unparser.is_opeq");
		in->attrs->erase("phc.unparser.is_global_stmt");
		in->attrs->erase("phc.unparser.starts_line");
		in->attrs->erase("phc.unparser.needs_curlies");
		in->attrs->erase("phc.unparser.needs_user_curlies");
		in->attrs->erase("phc.unparser.needs_brackets");
		in->attrs->erase("phc.unparser.needs_user_brackets");
	}

	void pre_assignment(AST_assignment* in)
	{
		// Assignments of the form $$e =& $d dont work if $$e is split
		// into a temporary first
		if (in->is_ref && in->variable->variable_name->classid() == AST_reflection::ID)
			in->variable->attrs->set_true("phc.lower_expr.no_temp");

		// We need references if we shred $x[0][1][etc] = ...;
		in->variable->attrs->set_true("phc.shredder.need_addr");

		// Variables on the RHS need references if $x =& $y is being used
		Wildcard<AST_variable>* rhs = new Wildcard<AST_variable> ();
		if (in->is_ref && in->match (new AST_assignment (new Wildcard<AST_variable>(), false /*ignore*/, rhs)))
			rhs->value->attrs->set_true ("phc.shredder.need_addr");

		// Is is not necessary to generate a temporary for the
		// top-level expression of an assignment
		if (in->expr->classid () != AST_array::ID)
			in->expr->attrs->set_true("phc.lower_expr.no_temp");
	}

	void pre_unset(AST_unset* in)
	{
		in->variable->attrs->set_true("phc.shredder.need_addr");
	}

	void pre_attribute(AST_attribute* in)
	{
		// Do not generate a temp to hold the default value of an
		// attribute
		if(in->expr != NULL)
			in->expr->attrs->set_true("phc.lower_expr.no_temp");

		generate_array_temps = false;
	}

	void post_attribute(AST_attribute* in)
	{
		generate_array_temps = true;
	}

	void pre_array_elem (AST_array_elem* in)
	{
		if (generate_array_temps == false)
		{
			if(in->key)
				in->key->attrs->set_true("phc.lower_expr.no_temp");
			if(in->val)
				in->val->attrs->set_true("phc.lower_expr.no_temp");
		}
	}

	void pre_static_declaration(AST_static_declaration* in)
	{
		// Do not generate a temp to hold the default value of a static var
		if(in->expr)
			in->expr->attrs->set_true("phc.lower_expr.no_temp");
	}

	void pre_directive (AST_directive* in)
	{
		// Do not generate a temp to hold the value of a directive
		// variable
		in->expr->attrs->set_true("phc.lower_expr.no_temp");
	}

	void pre_formal_parameter (AST_formal_parameter* in)
	{
		// Do not generate a temp to hold the value of a parameter's
		// default value
		if (in->expr)
			in->expr->attrs->set_true("phc.lower_expr.no_temp");

		generate_array_temps = false;
	}

	void post_formal_parameter (AST_formal_parameter* in)
	{
		generate_array_temps = true;
	}

	// TODO nested functions?
	void pre_method (AST_method* in)
	{
		return_by_ref = in->signature->is_ref;
	}

	void post_method (AST_method* in)
	{
		return_by_ref = false;
	}

	void post_return (AST_return* in)
	{
		if (return_by_ref 
			&& in->expr->classid () == AST_variable::ID)
			in->expr->attrs->set_true ("phc.shredder.need_addr");
	}

	void post_method_invocation (AST_method_invocation* in)
	{
		/* To be able to support includes with return statements, without
		 * dataflow, we dont shred their string arguments */
		Token_method_name* name = dynamic_cast<Token_method_name*>(in->method_name);
		if (name && (
					*name->value == "include"
					or *name->value == "require" 
					or *name->value == "include_once" 
					or *name->value == "require_once"))
		{
			List<AST_actual_parameter*>::const_iterator i;
			for (i = in->actual_parameters->begin (); i != in->actual_parameters->end(); i++)
			{
				if (dynamic_cast<Token_string*> ((*i)->expr))
					(*i)->expr->attrs->set_true("phc.lower_expr.no_temp");
			}

		}

		/* It isn't correct to shred variables which may be references at
		 * run-time, but where we cannot tell if they are at compile-time. The
		 * only occurrence of this in PHP is actual parameters. */
		List<AST_actual_parameter*>::const_iterator i;
		for (i = in->actual_parameters->begin (); i != in->actual_parameters->end(); i++)
		{
			if (dynamic_cast<AST_variable*> ((*i)->expr))
				(*i)->expr->attrs->set_true("phc.shredder.dont_shred");
		}

	}


	/* Statements can occur nested within expressions, in which case we'd like
	 * to simplify them. We mark assignments which occur as an eval_expr, then mark
	 * all other assignments as being nested_stmts.
	 */
	void pre_eval_expr (AST_eval_expr* in)
	{
		if (dynamic_cast<AST_assignment*> (in->expr))
		{
			in->expr->attrs->set_true("phc.shredder.non_nested_assignment");
		}
	}
};

// Some shredding will create variables which may be missed if done at the same
// time as the variable shredding.
class Early_shredder : public Lower_expr
{
public:

	/* Shred
	 *  $x = (list ($a, $b, $c) = array ($c, $b, a));
	 * into
	 *	  $PLA = array ($c, $b, $a);
	 *	  $c = $PLA[2];
	 *	  $b = $PLA[1];
	 *	  $a = $PLA[0];
	 *	  $x = $PLA; // note that left evaluates to the RHS of the assignment
	 *
	 *	Note the reverse order. This matters if you've arrays on the lhs.
	 *	Note that references arent allowed here.
	 */

	AST_expr* post_list_assignment(AST_list_assignment* in)
	{
		AST_variable* temp = fresh_var("PLA");

		assert (in->expr != NULL);

		bool use_ref = !is_ref_literal (in->expr);
		pieces->push_back(
				new AST_eval_expr(
					new AST_assignment(temp->clone (), use_ref, in->expr)));


		// reverse order
		List<AST_list_element*>::const_reverse_iterator i;
		int counter = in->list_elements->size () - 1;
		for (i = in->list_elements->rbegin (); 
				i != in->list_elements->rend ();
				i++)
		{
			// create the RHS
			List<AST_expr*> *array_indices = new List<AST_expr*> ();
			array_indices->push_back (new Token_int (counter));
			AST_variable* rhs = new AST_variable (
					NULL,
					temp->variable_name->clone(),
					array_indices);
			counter --;

			// list ($x, , $z) leaves a NULL
			if (*i == NULL)
				continue;

			// create the LHS
			// its either a variable or a nested list element
			AST_nested_list_elements* nested 
				= dynamic_cast <AST_nested_list_elements*> (*i);
			if (nested)
			{
				// convert into a list_assignment, and repeat
				pieces->push_back (new AST_eval_expr (
							post_list_assignment (
								new AST_list_assignment (nested->list_elements, rhs))));
			}
			else
			{
				AST_variable* var = dynamic_cast <AST_variable*> (*i);
				assert (var);
				// $c = $PLA[2];
				pieces->push_back( 
						new AST_eval_expr(
							new AST_assignment(var, false, rhs)));
			}
		}
		assert (counter == -1);

		// lists evaluate to their rvalue
		return temp;
	}

	/* Convert
	 *		$x++;
	 *	into
	 *		$x = $x + 1;
	 *
	 *	This must be done before $A::q is shredded.
	 */
	AST_expr* post_pre_op(AST_pre_op* in)
	{
		Token_op* op;

		if(*in->op->value == "--")
			op = new Token_op(new String("-"));
		else if(*in->op->value == "++")
			op = new Token_op(new String("+"));
		else
			assert(0);

		AST_variable* one = fresh_var("TSo");

		pieces->push_back(new AST_eval_expr(new AST_assignment(
						one,
						false,
						new Token_int(1))));
		pieces->push_back(new AST_eval_expr(new AST_assignment(
						in->variable->clone(),
						false,
						new AST_bin_op(
							in->variable->clone(),
							op,
							one->clone ()))));

		return in->variable->clone();
	}

	AST_expr* post_post_op(AST_post_op* in)
	{
		Token_op* op;

		if(*in->op->value == "--")
			op = new Token_op(new String("-"));
		else if(*in->op->value == "++")
			op = new Token_op(new String("+"));
		else
			assert(0);

		AST_variable* old_value = fresh_var("TS");
		AST_variable* one = fresh_var("TSo");

		pieces->push_back(new AST_eval_expr(new AST_assignment(
						old_value->clone (),
						false,
						in->variable->clone())));
		pieces->push_back(new AST_eval_expr(new AST_assignment(
						one->clone (),
						false,
						new Token_int(1))));
		pieces->push_back(new AST_eval_expr(new AST_assignment(
						in->variable->clone(),
						false,
						new AST_bin_op(
							in->variable->clone(),
							op,
							one))));

		return old_value;
	}


};

class Tidy_print : public AST_transform
{
	void pre_eval_expr (AST_eval_expr* in, List<AST_statement*>* out)
	{
		AST_assignment* agn = dynamic_cast<AST_assignment*> (in->expr);
		assert (agn);

		/* Convert print, in a similar fashion to echo. Print can only have 1 parameter though, and always return 1.
		 *   $x = print $y;
		 * into
		 *   $t2 = printf ("%s", $y); // $t2 can be discarded
		 *   $x = 1;
		 */
		Wildcard<AST_expr>* arg = new Wildcard<AST_expr>;
		AST_method_invocation* print = new AST_method_invocation (
				NULL,	
				new Token_method_name (new String ("print")),
				new List<AST_actual_parameter*> (
					new AST_actual_parameter (false, arg) // print can only have 1 argument
					));



		if (agn->expr->match (print))
		{
			// $t2 = printf ("%s", expr);
			AST_variable* t2 = fresh_var("TSp");
			out->push_back_all (shred (
						new AST_eval_expr (
							new AST_assignment(t2, false,
								new AST_method_invocation(
									NULL,
									new Token_method_name(new String("printf")),
									new List<AST_actual_parameter*>(
										new AST_actual_parameter(
											false, 
											new Token_string(new String("%s"))),
										new AST_actual_parameter(
											false,
											arg->value)
										))))));

			// $x = 1;
			out->push_back (new AST_eval_expr (
						new AST_assignment(agn->variable, false,
							new Token_int (1))));

			return;
		}
		else
		{
			out->push_back (in);;
		}
	}
};


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
	Echo_split ecs;
	in->transform_children (&ecs);

	Desugar desugar;
	in->transform_children(&desugar);

	// Shredding which creates more variables and may be missed
	Early_shredder es;
	in->transform_children(&es);

	Annotate ann;
	in->visit(&ann);

	Lower_expr::children_php_script(in);

	// Its easier to do this after shredding, since its hard to support "print
	// print print $x;" without it.
	Tidy_print tp;
	in->transform_children (&tp);


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
	pieces->push_back(new AST_unset (var->clone ()));

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

