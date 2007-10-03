/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * shredder (n.): a machine that tears objects into smaller pieces.
 * (Transform the AST into 3AC-like code)
 */

#ifndef PHC_SHREDDER_H
#define PHC_SHREDDER_H

#include "Lower_expr.h"
#include "fresh.h"
#include "process_ast/Consistency_check.h"

List<AST_statement*>* shred (List<AST_statement*>* in);
List<AST_statement*>* shred (AST_statement* in);

class Shredder : public Lower_expr
{
public:
	void children_php_script(AST_php_script* in);
	void post_nop(AST_nop* in);

public:
	AST_variable* post_variable(AST_variable* in);
	AST_expr* post_bin_op(AST_bin_op* in);
	AST_expr* post_unary_op(AST_unary_op* in);
	AST_expr* post_method_invocation(AST_method_invocation* in);
	AST_expr* post_int(Token_int* in);
	AST_expr* post_real(Token_real* in);
	AST_expr* post_bool(Token_bool* in);
	AST_expr* post_string(Token_string* in);
	AST_expr* post_null(Token_null* in);
	AST_expr* post_constant (AST_constant* in);
	AST_expr* post_array(AST_array* in);
	AST_expr* post_assignment(AST_assignment* in);
	AST_expr* post_op_assignment(AST_op_assignment* in);
	AST_expr* pre_ignore_errors(AST_ignore_errors* in);
	AST_expr* post_ignore_errors(AST_ignore_errors* in);
	void pre_eval_expr (AST_eval_expr* in, List<AST_statement*>* out);
};


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

	// All eval_expr must be assignments; if they are not, we generate
	// a dummy assignment on the LHS
	void pre_eval_expr(AST_eval_expr* in, List<AST_statement*>* out)
	{
		// remove variables on their own
		if (in->expr->classid() == AST_variable::ID)
			return;

		// Don't generate an assignment for unset
		AST_expr* unset = new AST_method_invocation(NULL, "unset", new Wildcard<AST_expr>);

		if(in->expr->classid() != AST_assignment::ID && 
		   in->expr->classid() != AST_op_assignment::ID &&
		   in->expr->classid() != AST_list_assignment::ID &&
		  !in->expr->match(unset))
		{
			AST_variable* var = fresh_var ("TSe");
			var->attrs->set_true ("phc.codegen.unused");

			in->expr = new AST_assignment(var, false, in->expr);
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
			in->expr->attrs->set_true ("phc.codegen.unused");
		}

		out->push_back(in);
	}
};

class Very_early_shredder : public Lower_expr
{
public:

	/* Convert
	 *		++$x;
	 *	into
	 *		$u = ++$x; // mark $u as unused
	 *		$x;
	 */
	AST_expr* post_pre_op(AST_pre_op* in)
	{
		// $u = ++$x;
		AST_variable* unused = fresh_var ("TSpri");
		unused->attrs->set_true ("phc.codegen.unused");
		pieces->push_back (new AST_eval_expr (
				new AST_assignment (
					unused,
					false,
					in)));

		// $x
		return in->variable->clone ();;
	}

	/* Special case:
	 *	If 
	 *		$x++ 
	 *	is found on its own, convert directly into
	 *		++$x;
	 *
	 *	This avoids an extra statement being issued by post_post_op.
	 *	This should be replaced with data-flow at a later date.
	 */
	void pre_eval_expr (AST_eval_expr* in, List<AST_statement*>* out)
	{
		if (AST_post_op* post_op = dynamic_cast<AST_post_op*> (in->expr))
		{
			in->expr = new AST_pre_op (post_op->op, post_op->variable);
		}
		out->push_back (in);
	}

	/* Convert
	 *		$x++;
	 *	into
	 *		$t = $x;
	 *		$u = ++$x; // mark $u as unused
	 *		$t;
	 */
	AST_expr* post_post_op(AST_post_op* in)
	{
		AST_variable* old_value = fresh_var("TS");

		// $t = $x
		pieces->push_back (new AST_eval_expr (new AST_assignment(
						old_value->clone (),
						false,
						in->variable->clone())));

		// $u = ++$x;
		AST_variable* unused = fresh_var ("TSpoi");
		unused->attrs->set_true ("phc.codegen.unused");
		pieces->push_back (new AST_eval_expr (
				new AST_assignment (
					unused,
					false,
					new AST_pre_op (
						in->op,
						in->variable))));

		// $t
		return old_value;
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

  // op_assignments are never by reference
	void pre_op_assignment(AST_op_assignment* in)
	{
		// We need references if we shred $x[0][1][etc] = ...;
		in->variable->attrs->set_true("phc.shredder.need_addr");

    // We do need a temporary for the expression of the op_assignment,
    // because it will be the right operand to a binary operator
	}

	void pre_post_op (AST_post_op* in)
	{
		in->variable->attrs->set_true("phc.shredder.need_addr");
	}

	void pre_pre_op (AST_pre_op* in)
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
		generate_array_temps = false;
		// Do not generate a temp to hold the default value of a static var
		if(in->expr)
			in->expr->attrs->set_true("phc.lower_expr.no_temp");
	}

	void post_static_declaration(AST_static_declaration* in)
	{
		generate_array_temps = true;
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
		if (in->expr->classid() == AST_assignment::ID ||
		    in->expr->classid() == AST_op_assignment::ID ||
			in->expr->classid() == AST_list_assignment::ID)
		{
			in->expr->attrs->set_true("phc.shredder.non_nested_assignment");
		}

		if (in->expr->classid() == AST_method_invocation::ID)
		{
			// Do not generate temps for top-level method invocations
			in->expr->attrs->set_true("phc.lower_expr.no_temp");
		}
	}
};

// Some shredding will create variables which may be missed if done
// at the same time as the variable shredding.
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
};

class Tidy_print : public AST_transform
{
	void pre_eval_expr (AST_eval_expr* in, List<AST_statement*>* out)
	{
		AST_assignment* agn = dynamic_cast<AST_assignment*> (in->expr);

		/* Convert print, in a similar fashion to echo. Print can only have 1 parameter though, and always return 1.
		 *   $x = print $y;
		 * into
		 *   $t2 = printf ("%s", $y); // $t2 can be discarded
		 *   $x = 1;
		 *
		 * If $x is unused, we have
		 *	  $x = printf ("%s", $y);
		 */
		Wildcard<AST_expr>* arg = new Wildcard<AST_expr>;
		AST_method_invocation* print = new AST_method_invocation (
				NULL,	
				new Token_method_name (new String ("print")),
				new List<AST_actual_parameter*> (
					new AST_actual_parameter (false, arg) // print can only have 1 argument
					));

		if (agn && agn->expr->match (print))
		{
			// $t2 = printf ("%s", expr);
			bool unused = agn->variable->attrs->is_true ("phc.codegen.unused");

			AST_variable* t2 = agn->variable;
			if (not unused)
				t2 = fresh_var ("TSp");

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


			// This isnt necessary 
			if (not unused)
			{
				// $x = 1;
				out->push_back (new AST_eval_expr (
							new AST_assignment(agn->variable, false,
								new Token_int (1))));
			}

			return;
		}
		else
		{
			out->push_back (in);;
		}
	}
};

#endif // PHC_SHREDDER_H
