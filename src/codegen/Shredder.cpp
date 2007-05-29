/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Transform the AST into 3AC-like code.
 */

#include "Shredder.h"
#include "fresh.h"

// For development only
#include "process_ast/XML_unparser.h"
#include "process_ast/PHP_unparser.h"

class Desugar : public AST_transform
{
public:
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

 	// Global is translated into a reference to the GLOBALS array
	void pre_global(AST_global* in, List<AST_statement*>* out)
	{
		Token_variable_name* name;
		name = dynamic_cast<Token_variable_name*>(in->variable_name);
	
		if(name != NULL)
		{
			out->push_back(new AST_eval_expr(new AST_assignment(
				new AST_variable(NULL, name->clone (), new List<AST_expr*>),
				true,
				new AST_variable(
					NULL, 
					new Token_variable_name(new String("GLOBALS")),
					new List<AST_expr*>(new Token_string(
						name->value->clone(),
						name->value->clone()
				))))));
		}
		else
		{
			AST_reflection* reflection;
			reflection = dynamic_cast<AST_reflection*>(in->variable_name);
			assert(reflection != NULL);
	
			out->push_back(new AST_eval_expr(new AST_assignment(
				new AST_variable(NULL, reflection, new List<AST_expr*>),
				true,
				new AST_variable(
					NULL, 
					new Token_variable_name(new String("GLOBALS")),
					new List<AST_expr*>(reflection->expr)
				))));
		}
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

	// Since the shredder changes all eval_expr into assignments, it will
	// change echo("hi") to $Tx = echo("hi"); but since "echo" isn't a true
	// function call in PHP, this will generate incorrect PHP code. For that
	// reason, we translate echo(x) to printf("%s",x) here.
	AST_expr* pre_method_invocation(AST_method_invocation* in)
	{
		Wildcard<AST_expr>* arg = new Wildcard<AST_expr>;
		AST_method_invocation* echo = new AST_method_invocation(
			NULL,	
			new Token_method_name(new String("echo")),
			new List<AST_actual_parameter*>(
				new AST_actual_parameter(false, arg)
			));
		AST_method_invocation* print = new AST_method_invocation(
			NULL,	
			new Token_method_name(new String("print")),
			new List<AST_actual_parameter*>(
				new AST_actual_parameter(false, arg)
			));
	
		if(in->match(echo) || in->match(print))
		{
			return new AST_method_invocation(
				NULL,
				new Token_method_name(new String("printf")),
				new List<AST_actual_parameter*>(
					new AST_actual_parameter(
						false, 
						new Token_string(new String("%s"), new String("%s"))),
					new AST_actual_parameter(
						false,
						arg->value)
				));
		}
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
	void pre_node(AST_node* in)
	{
		in->attrs->erase("phc.unparser.is_opeq");
		in->attrs->erase("phc.unparser.is_global_stmt");
		in->attrs->erase("phc.unparser.starts_line");

		// TODO: I *think* this is correct, but I'm not sure
		in->attrs->erase("phc.unparser.needs_curlies");
	}

	void pre_assignment(AST_assignment* in)
	{
		// Assignments of the form $$e =& $d dont work if $$e is split into a temporary first
		if (in->is_ref && in->variable->variable_name->classid() == AST_reflection::ID)
			in->variable->attrs->set_true("phc.lower_expr.no_temp");

		in->variable->attrs->set_true("phc.shredder.need_addr");

		// Is is not necessary to generate a temporary for the top-level
		// expression of an assignment
		in->expr->attrs->set_true("phc.lower_expr.no_temp");
	}

	void pre_unset(AST_unset* in)
	{
		in->variable->attrs->set_true("phc.shredder.need_addr");
	}

	void pre_attribute(AST_attribute* in)
	{
		// Do not generate a temp to hold the default value of an attribute
		if(in->expr != NULL)
			in->expr->attrs->set_true("phc.lower_expr.no_temp");
	}

	void pre_static_declaration(AST_static_declaration* in)
	{
		// Do not generate a temp to hold the default value of a static var
		if(in->expr != NULL)
			in->expr->attrs->set_true("phc.lower_expr.no_temp");
	}

	void pre_directive (AST_directive* in)
	{
		// Do not generate a temp to hold the value of a directive
		// variable
		in->expr->attrs->set_true("phc.lower_expr.no_temp");
	}

};

/*
 * Remove unparser attributes and desugar
 */

void Shredder::children_php_script(AST_php_script* in)
{
	Desugar desugar;
	in->transform_children(&desugar);

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
 *	$T3 =& $T2[3];
 *
 * If the variable occurs on the LHS of an assignment (if the attribute
 * "phc.shredder.need_addr" is set), we stop one short, and use that as the
 * LHS. In the example above, we'd stop at the assignment to $T2, and then
 * use 
 *
 *   $T2[3] = ...
 *
 * as the LHS of the assignment. This isn't strictly necessary for array
 * assignment (since we are using reference assignment), but it is strictly
 * necessary if the variable is the argument to a call to "unset", for example.
 *
 * Note that it is important to use reference assignment, because when we
 * assign to $T2[2] above, we want the original object $c to be modified.
 */

AST_variable* Shredder::post_variable(AST_variable* in)
{
	AST_variable* prev = in;
	
	int num_pieces = 
		  (in->target != NULL ? 1 : 0) 
		+ in->array_indices->size()
		- (in->attrs->is_true("phc.shredder.need_addr") ? 1 : 0);

	// translate ${$x}[1] to $T = ${$x}; $T[1] but only if no target is set
	if(in->target == NULL 
		&& in->variable_name->classid() == AST_reflection::ID
		&& !in->attrs->is_true ("phc.lower_expr.no_temp"))
	{
		AST_variable* temp = fresh_var("TSr");
		pieces->push_back(new AST_eval_expr(new AST_assignment(
			temp->clone (), true,
			new AST_variable(
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
			temp->clone (), true,
			new AST_variable(
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
			temp->clone (), true,
			new AST_variable(
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
		prev->array_indices->push_back(in->array_indices->front()->clone ());
		in->array_indices->pop_front();
	}

	return prev;
}

/*
 * Binary and unary operators
 *
 * The "lazy" binary operators (&&, ||, and friends) are not dealt with here, 
 * but in the lowering pass. Pre and post operators are translated to binary
 * operators.
 */

AST_expr* Shredder::post_bin_op(AST_bin_op* in)
{
	return eval(in);
}

AST_expr* Shredder::post_unary_op(AST_unary_op* in)
{
	return eval(in);
}
	
AST_expr* Shredder::post_pre_op(AST_pre_op* in)
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

AST_expr* Shredder::post_post_op(AST_post_op* in)
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

/*
 * Array literals
 */

AST_expr* Shredder::post_array(AST_array* in)
{
	String* temp = fresh("TSa");
	List<AST_array_elem*>::const_iterator i;
	
	for(i = in->array_elems->begin(); i != in->array_elems->end(); i++)
	{
		AST_expr* key;

		if((*i)->key != NULL)
			key = (*i)->key;
		else
			key = NULL;

		pieces->push_back(new AST_eval_expr(new AST_assignment(
			new AST_variable(
				NULL,
				new Token_variable_name(temp->clone()),
				new List<AST_expr*>(key)),
			(*i)->is_ref,
			(*i)->val
			)));
	}
	
	return new AST_variable(
		NULL,
		new Token_variable_name(temp),
		new List<AST_expr*>());
}

/* Shred
 *  $x = (list ($a, $b, $c) = array ($c, $b, a));
 * into
 *	  $Tarr = array ($c, $b, $a); // hopefully this is already done
 *	  $c = $Tarr[2];
 *	  $b = $Tarr[1];
 *	  $a = $Tarr[0];
 *	  $x = $Tarr;
 *
 *	Note the reverse order. This matters if you've arrays on the lhs. note that references arent allowed here.
 */

AST_expr* Shredder::pre_list_assignment(AST_list_assignment* in)
{
	AST_variable* temp = fresh_var("PLA");

	assert (in->expr != NULL);
	pieces->push_back(
		new AST_eval_expr(
			new AST_assignment(temp->clone (), false, in->expr)));

	// Hopefully nested lists will be handled by the visitor by magic


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
		AST_variable* rhs = 
			new AST_variable (NULL, 
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
			// $c = $Tarr[2];
			pieces->push_back( 
				new AST_eval_expr(
					new AST_assignment(var, false, rhs)));
		}
	}
	assert (counter == -1);

	// lists evaluate to their rvalue
	return temp;
}
